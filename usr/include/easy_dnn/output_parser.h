// Copyright (c) 2021 Horizon Robotics.All Rights Reserved.
//
// The material in this file is confidential and contains trade secrets
// of Horizon Robotics Inc. This is proprietary information owned by
// Horizon Robotics Inc. No part of this work may be disclosed,
// reproduced, copied, transmitted, or used in any way for any purpose,
// without the express written permission of Horizon Robotics Inc.

#ifndef _EASY_DNN_OUTPUT_PARSER_H_
#define _EASY_DNN_OUTPUT_PARSER_H_

#include <easy_dnn/data_structure.h>

#include <memory>
#include <vector>

#include "description.h"

namespace hobot {
namespace easy_dnn {
class OutputParser {
 public:
  virtual ~OutputParser() = default;
};

class SingleBranchOutputBaseParser : public OutputParser {
 public:
  virtual int32_t Parse(
      std::shared_ptr<DNNResult>& output,
      std::vector<std::shared_ptr<InputDescription>>& input_descriptions,
      std::shared_ptr<OutputDescription>& output_description,
      std::shared_ptr<DNNTensor>& output_tensor) = 0;
};

class MultiBranchOutputBaseParser : public OutputParser {
 public:
  virtual int32_t Parse(
      std::shared_ptr<DNNResult>& output,
      std::vector<std::shared_ptr<InputDescription>>& input_descriptions,
      std::shared_ptr<OutputDescription>& output_descriptions,
      std::shared_ptr<DNNTensor>& output_tensor,
      std::vector<std::shared_ptr<OutputDescription>>& depend_output_descs,
      std::vector<std::shared_ptr<DNNTensor>>& depend_output_tensors,
      std::vector<std::shared_ptr<DNNResult>>& depend_outputs) = 0;
};

/**
 * Parser for a single output branch which does not depends any other branch
 * `TParserResult` must be inherit form `DNNResult`, otherwise parse will be
 * failed
 */
template <typename ResultType>
class SingleBranchOutputParser : public SingleBranchOutputBaseParser {
  /**
   * Parse tensor accord to input & output descriptions
   * @param[inout] output
   * @param[in] input_descriptions
   * @param[in] output_description
   * @param[in] output_tensor
   * @return 0 if success, return defined error code otherwise
   */
 public:
  virtual int32_t Parse(
      std::shared_ptr<ResultType>& output,
      std::vector<std::shared_ptr<InputDescription>>& input_descriptions,
      std::shared_ptr<OutputDescription>& output_description,
      std::shared_ptr<DNNTensor>& output_tensor) = 0;
  /**
   * parse invoked by model_infer_task(model_roi_infer_task)
   */
  int32_t Parse(
      std::shared_ptr<DNNResult>& output,
      std::vector<std::shared_ptr<InputDescription>>& input_descriptions,
      std::shared_ptr<OutputDescription>& output_description,
      std::shared_ptr<DNNTensor>& output_tensor) final {
    std::shared_ptr<ResultType> result = nullptr;
    if (!output) {
      result = std::make_shared<ResultType>();
      output = result;
    } else {
      result = std::dynamic_pointer_cast<ResultType>(output);
      // Reset the result since it's a new parsing proccess
      result->Reset();
    }
    return !result ? -1
                   : Parse(result,
                           input_descriptions,
                           output_description,
                           output_tensor);
  }
};

/**
 * Parse for a branch which depends on other branch (description, output tensor
 *  and output result)
 * `TParserResult` must be inherit form `DNNResult`, otherwise parse will be
 * failed
 */
template <typename ResultType>
class MultiBranchOutputParser : public MultiBranchOutputBaseParser {
  /**
   * @param[inout] output
   * @param[in] input_descriptions
   * @param[in] output_descriptions
   * @param[in] output_tensor
   * @param[in] depend_output_descs dependencies output description
   * @param[in] depend_output_tensors dependencies output tensor
   * @param[in] depend_outputs dependencies output
   * @return 0 if success, return defined error code otherwise
   */
 public:
  virtual int32_t Parse(
      std::shared_ptr<ResultType>& output,
      std::vector<std::shared_ptr<InputDescription>>& input_descriptions,
      std::shared_ptr<OutputDescription>& output_descriptions,
      std::shared_ptr<DNNTensor>& output_tensor,
      std::vector<std::shared_ptr<OutputDescription>>& depend_output_descs,
      std::vector<std::shared_ptr<DNNTensor>>& depend_output_tensors,
      std::vector<std::shared_ptr<DNNResult>>& depend_outputs) = 0;
  /**
   * Parse invoked by model_infer_task(model_roi_infer_task)
   */
  int32_t Parse(
      std::shared_ptr<DNNResult>& output,
      std::vector<std::shared_ptr<InputDescription>>& input_descriptions,
      std::shared_ptr<OutputDescription>& output_descriptions,
      std::shared_ptr<DNNTensor>& output_tensor,
      std::vector<std::shared_ptr<OutputDescription>>& depend_output_descs,
      std::vector<std::shared_ptr<DNNTensor>>& depend_output_tensors,
      std::vector<std::shared_ptr<DNNResult>>& depend_outputs) final {
    std::shared_ptr<ResultType> result = nullptr;
    if (!output) {
      result = std::make_shared<ResultType>();
      output = result;
    } else {
      result = std::dynamic_pointer_cast<ResultType>(output);
    }
    return !result ? -1
                   : Parse(result,
                           input_descriptions,
                           output_descriptions,
                           output_tensor,
                           depend_output_descs,
                           depend_output_tensors,
                           depend_outputs);
  }
};

}  // namespace easy_dnn
}  // namespace hobot
#endif  // _EASY_DNN_OUTPUT_PARSER_H_
