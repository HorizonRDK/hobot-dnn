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

#ifndef _EASY_DNN_INPUT_PROCESSOR_H_
#define _EASY_DNN_INPUT_PROCESSOR_H_

#include <memory>
namespace hobot {
namespace easy_dnn {

class DNNInput;
class DNNTensor;

class InputProcessor {
 public:
  /**
   * InputProcessor
   * @param[inout] tensor
   * @param[in] input_desc
   * @param[in]  input
   * @return 0 if success, return defined error code otherwise
   */
  virtual int32_t Process(std::shared_ptr<DNNTensor>& tensor,
                          std::shared_ptr<InputDescription>& input_desc,
                          std::shared_ptr<DNNInput>& input) = 0;
  virtual ~InputProcessor() = default;
};

}  // namespace easy_dnn
}  // namespace hobot

#endif  // _EASY_DNN_INPUT_PROCESSOR_H_
