// Copyright (c) 2021 Horizon Robotics.All Rights Reserved.
//
// The material in this file is confidential and contains trade secrets
// of Horizon Robotics Inc. This is proprietary information owned by
// Horizon Robotics Inc. No part of this work may be disclosed,
// reproduced, copied, transmitted, or used in any way for any purpose,
// without the express written permission of Horizon Robotics Inc.

#ifndef _EASY_DNN_OUTPUT_PARSER_H_
#define _EASY_DNN_OUTPUT_PARSER_H_

#include <memory>
#include <vector>

#include "easy_dnn/abandon.h"

namespace hobot {
namespace easy_dnn {
class OutputBaseParser : public OutputParser {
 public:
  virtual int32_t Parse(
      std::vector<std::shared_ptr<DNNResult>>& outputs,
      std::vector<std::shared_ptr<OutputDescription>>& output_descriptions,
      std::vector<std::shared_ptr<DNNTensor>>& output_tensors) = 0;
};

}  // namespace easy_dnn
}  // namespace hobot
#endif  // _EASY_DNN_OUTPUT_PARSER_H_
