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

#ifndef _EASY_DNN_VERSION_H_
#define _EASY_DNN_VERSION_H_
#define EASYDNN_VERSION_MAJOR 1U
#define EASYDNN_VERSION_MINOR 6U
#define EASYDNN_VERSION_PATCH 1U

namespace hobot {
namespace easy_dnn {

class Version {
 public:
  static Version* GetInstance();

  /**
   * Get the libDNN version
   * @return return the libDNN version
   */
  virtual const char* GetLibDNNVersion() = 0;
  /**
   * Get the hbrt version
   * @return return the hbrt version
   */
  virtual const char* GetHbrtVersion() = 0;
  /**
   * Get the easydnn version
   * @return return the easydnn version
   */
  virtual const char* GetEasyDNNVersion() = 0;

  virtual ~Version() = default;
};

}  // namespace easy_dnn
}  // namespace hobot

#endif  // _EASY_DNN_VERSION_H_
