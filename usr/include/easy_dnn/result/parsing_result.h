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

#ifndef _EASY_DNN_RESULT_PARSING_RESULT_H_
#define _EASY_DNN_RESULT_PARSING_RESULT_H_

#include <vector>

#include "easy_dnn/data_structure.h"

namespace hobot {
namespace easy_dnn {

struct DNNDimension {
  int32_t height;
  int32_t width;
  int32_t channel;
};

class DepthResult : public DNNResult {
 public:
  std::vector<float> depth;
  int32_t height;
  int32_t width;
  int32_t channel;
  void Reset() override { depth.clear(); }
};

class ElevationResult : public DNNResult {
 public:
  std::vector<float> elevation;
  int32_t height;
  int32_t width;
  int32_t channel;
  void Reset() override { elevation.clear(); }
};

class ParsingResult : public DNNResult {
 public:
  std::vector<uint8_t> data;
  int32_t height;
  int32_t width;
  int32_t channel;

  void Reset() override { data.clear(); }
};

class ResidualResult : public DNNResult {
 public:
  std::vector<std::vector<float>> data;
  int32_t height;
  int32_t width;
  int32_t channel;

  void Reset() override { data.clear(); }
};

}  // namespace easy_dnn
}  // namespace hobot
#endif  // _EASY_DNN_RESULT_PARSING_RESULT_H_
