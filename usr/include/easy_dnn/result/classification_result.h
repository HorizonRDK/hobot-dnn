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

#ifndef _EASY_DNN_RESULT_CLASSIFICATION_RESULT_H_
#define _EASY_DNN_RESULT_CLASSIFICATION_RESULT_H_

#include <string>
#include <vector>

#include "easy_dnn/data_structure.h"

namespace hobot {
namespace easy_dnn {

class ClassificationResult : public DNNResult {
 public:
  float max_conf;
  int32_t class_id;
  std::string class_name;
};

class HaloClassificationResult : public DNNResult {
 public:
  std::vector<int8_t> features_;
  void Reset() override { features_.clear(); }
};

}  // namespace easy_dnn
}  // namespace hobot

#endif  // _EASY_DNN_RESULT_CLASSIFICATION_RESULT_H_
