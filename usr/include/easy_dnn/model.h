// Copyright (c) [2021-2023] [Horizon Robotics].
//
// You can use this software according to the terms and conditions of
// the Apache v2.0.
// You may obtain a copy of Apache v2.0. at:
//
//     http: //www.apache.org/licenses/LICENSE-2.0
//
// THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF
// ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// NON-INFRINGEMENT, MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
// See Apache v2.0 for more details.

#ifndef _EASY_DNN_MODEL_IMPL_H_
#define _EASY_DNN_MODEL_IMPL_H_
#include <memory>
#include <string>
#include <vector>

#include "data_structure.h"
#include "dnn/hb_dnn.h"

namespace hobot {
namespace easy_dnn {

class InputDescription;
class InputProcessor;
class OutputDescription;
class OutputParser;

class Model {
 public:
  /**
   * Get model handle
   * @return model handle
   */
  virtual hbDNNHandle_t GetDNNHandle() = 0;

  /**
   * Get model name
   * @return model name
   */
  virtual const std::string& GetName() = 0;

  /**
   * Get input count
   * @return input count
   */
  virtual int32_t GetInputCount() = 0;

  /**
   * Get input name
   * @param[out] input_name
   * @param[in] input_index
   * @return 0 if success, return defined error code otherwise
   */
  virtual int32_t GetInputName(std::string& input_name,
                               int32_t input_index) = 0;

  /**
   * Get input source
   * @param[out] input_source
   * @param[in] input_index
   * @return 0 if success, return defined error code otherwise
   */
  virtual int32_t GetInputSource(int32_t& input_source,
                                 int32_t input_index) = 0;

  /**
   * Get input description
   * @param[out] input_desc, description for input, only string
   * @param[in] input_index
   * @return 0 if success, return defined error code otherwise
   */
  virtual int32_t GetInputDescription(std::string& input_desc,
                                      int32_t input_index) = 0;

  /**
   * Get input description
   * @param[out] input_desc, description for input
   * @param[out] size, description size
   * @param[out] type, can be string(1) or binary(2)
   * @param[in] input_index
   * @return 0 if success, return defined error code otherwise
   */
  virtual int32_t GetInputDescription(const char** input_desc,
                                      uint32_t& size,
                                      int32_t& type,
                                      int32_t input_index) = 0;

  /**
   * Get input description
   * @param[out] input_desc
   * @param[in] input_index
   * @return 0 if success, return defined error code otherwise
   */
  virtual int32_t GetInputDescription(
      std::shared_ptr<InputDescription>& input_desc, int32_t input_index) = 0;

  /**
   * Update input description
   * @param[in] input_desc
   * @return 0 if success, return defined error code otherwise
   */
  virtual int32_t SetInputDescription(
      std::shared_ptr<InputDescription>& input_desc) = 0;

  /**
   * Get input processor
   * @param[out] input_processor
   * @param[in] input_index
   * @return 0 if success, return defined error code otherwise
   */
  virtual int32_t GetInputProcessor(
      std::shared_ptr<InputProcessor>& input_processor,
      int32_t input_index) = 0;

  /**
   * Update input processor
   * @param[in] input_index
   * @param[in] input_processor
   * @return 0 if success, return defined error code otherwise
   */
  virtual int32_t SetInputProcessor(
      int32_t input_index,
      std::shared_ptr<InputProcessor>& input_processor) = 0;

  /**
   * Get input tensor properties
   * @param[out] tensor_properties
   * @param[in] input_index
   * @return 0 if success, return defined error code otherwise
   */
  virtual int32_t GetInputTensorProperties(
      hbDNNTensorProperties& tensor_properties, int32_t input_index) = 0;

  /**
   * Get output count
   * @return output count
   */
  virtual int32_t GetOutputCount() = 0;

  /**
   * Get output name
   * @param[out] output_name
   * @param[in] output_index
   * @return 0 if success, return defined error code otherwise
   */
  virtual int32_t GetOutputName(std::string& output_name,
                                int32_t output_index) = 0;

  /**
   * Get output description
   * @param[out] output_desc, description for output, only string
   * @param[in] output_index
   * @return 0 if success, return defined error code otherwise
   */
  virtual int32_t GetOutputDescription(std::string& output_desc,
                                       int32_t output_index) = 0;

  /**
   * Get input description
   * @param[out] output_desc, description for output
   * @param[out] size, description size
   * @param[out] type, can be string(1) or binary(2)
   * @param[in] output_index
   * @return 0 if success, return defined error code otherwise
   */
  virtual int32_t GetOutputDescription(const char** output_desc,
                                       uint32_t& size,
                                       int32_t& type,
                                       int32_t output_index) = 0;

  /**
   * Get output description
   * @param[out] output_desc
   * @param[in] output_index
   * @return 0 if success, return defined error code otherwise
   */
  virtual int32_t GetOutputDescription(
      std::shared_ptr<OutputDescription>& output_desc,
      int32_t output_index) = 0;

  /**
   * Update output description
   * @param[in] output_desc
   * @return 0 if success, return defined error code otherwise
   */
  virtual int32_t SetOutputDescription(
      std::shared_ptr<OutputDescription>& output_desc) = 0;

  /**
   * Get output parser
   * @param[out] output_parser
   * @param[in] output_index
   * @return 0 if success, return defined error code otherwise
   */
  virtual int32_t GetOutputParser(std::shared_ptr<OutputParser>& output_parser,
                                  int32_t output_index) = 0;

  /**
   * Get output parser
   * @param[in] output_index
   * @param[in] output_parser
   * @return 0 if success, return defined error code otherwise
   */
  virtual int32_t SetOutputParser(
      int32_t output_index, std::shared_ptr<OutputParser>& output_parser) = 0;

  /**
   * Get output tensor properties
   * @param[out] tensor_properties
   * @param[in] output_index
   * @return 0 if success, return defined error code otherwise
   */
  virtual int32_t GetOutputTensorProperties(
      hbDNNTensorProperties& tensor_properties, int32_t output_index) = 0;

  /**
   * Get output operator type
   * @param[out] type
   * @param[in] output_index
   * @return 0 if success, return defined error code otherwise
   */
  virtual int32_t GetOutputOperatorType(int32_t& type,
                                        int32_t output_index) = 0;

  /**
   * Get model estimate execute latency, it's real-time calculated based
   *  on historical statistics
   *  @param[out] estimate_latency
   * @return 0 if success, return defined error code otherwise
   */
  virtual int32_t GetEstimateLatency(int32_t& estimate_latency) = 0;

  /**
   * Get model tag
   * @param[out] tag
   * @return 0 if success, return defined error code otherwise
   */
  virtual int32_t GetTag(const char** tag) = 0;

  /**
   * Get model profiler
   * @param[out] profiler
   * @return 0 if success, return defined error code otherwise
   */
  virtual int32_t GetProfiler(Profiler& profiler) = 0;

  /**
   * Load Output Parser Plugin from file
   * @param[in] plugin_path
   * @return 0 if success, return defined error code otherwise
   */
  virtual int32_t LoadOutputParserPlugin(std::string const& plugin_path) = 0;

  virtual ~Model() = default;
};

}  // namespace easy_dnn
}  // namespace hobot

#endif  // _EASY_DNN_MODEL_IMPL_H_
