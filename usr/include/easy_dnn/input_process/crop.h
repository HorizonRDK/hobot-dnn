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

#ifndef _EASY_DNN_INPUT_PROCESS_CROP_H_
#define _EASY_DNN_INPUT_PROCESS_CROP_H_

#include <memory>
#include <ostream>
#include <string>

#include "easy_dnn/description.h"
#include "easy_dnn/input_processor.h"

namespace hobot {
namespace easy_dnn {

/**
 *            image_width, image_width_stride
 *      ┌---------------------------------------┐
 *      |                               |       |
 *      |                               |       |
 *      |       (x,y)----------┐        |       |
 *      |       |              |        |       |
 *      |       |              |        |       |   image_height
 *      |       |              |height  |       |
 *      |       |              |        |       |
 *      |       |              |        |       |
 *      |       └--------------┘        |       |
 *      |             width             |       |
 *      |                               |       |
 *      |                               |       |
 *      └-------------------------------┘-------┘
 */

class CropDescription : public InputDescription {
 public:
  CropDescription(Model* model,
                  int32_t index,
                  std::string type = "",
                  int32_t x = 0,
                  int32_t y = 0,
                  int32_t width = 0,
                  int32_t height = 0)
      : InputDescription(model, index, type),
        x(x),
        y(y),
        width(width),
        height(height) {}

  int32_t x;
  int32_t y;
  int32_t width;   // 0 means crop to the right edge [x,...]
  int32_t height;  // 0 means crop to the bottom edge [y, ...]

  friend std::ostream& operator<<(std::ostream& os, CropDescription* desc) {
    os << "CropDescription: x=" << desc->x << ", y=" << desc->y
       << ", width=" << desc->width << ", height=" << desc->height;
    return os;
  }
};

class CropProcessor : public InputProcessor {
 public:
  int32_t Process(std::shared_ptr<DNNTensor>& tensor,
                  std::shared_ptr<InputDescription>& input_desc,
                  std::shared_ptr<DNNInput>& input) override;
};

}  // namespace easy_dnn
}  // namespace hobot

#endif  // _EASY_DNN_INPUT_PROCESS_CROP_H_
