// Copyright (c) 2021 Horizon Robotics.All Rights Reserved.
//
// The material in this file is confidential and contains trade secrets
// of Horizon Robotics Inc. This is proprietary information owned by
// Horizon Robotics Inc. No part of this work may be disclosed,
// reproduced, copied, transmitted, or used in any way for any purpose,
// without the express written permission of Horizon Robotics Inc.

#ifndef _EASY_DNN_VERSION_H_
#define _EASY_DNN_VERSION_H_

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
