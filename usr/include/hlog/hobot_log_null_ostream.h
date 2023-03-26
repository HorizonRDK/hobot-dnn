// Copyright (c) [2021-2022] [Horizon Robotics][Horizon Bole].
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

#ifndef HLOG_HOBOT_LOG_NULL_OSTREAM_H_
#define HLOG_HOBOT_LOG_NULL_OSTREAM_H_

#include <iostream>
#include <string>
#include <utility>

#include "hlog/log_define.h"

namespace hobot {
namespace hlog {

class HLOG HobotLogNullOStream {
 public:
  HobotLogNullOStream(const char* file, const uint64_t line,
                      hobot::hlog::LogLevel level);
};

HLOG HobotLogNullOStream&& operator<<(HobotLogNullOStream&& out,
                                      std::string& content);
HLOG HobotLogNullOStream&& operator<<(HobotLogNullOStream&& out,
                                      const char* content);
HLOG HobotLogNullOStream&& operator<<(HobotLogNullOStream&& out,
                                      int8_t content);
HLOG HobotLogNullOStream&& operator<<(HobotLogNullOStream&& out,
                                      uint8_t content);
HLOG HobotLogNullOStream&& operator<<(HobotLogNullOStream&& out,
                                      int16_t content);
HLOG HobotLogNullOStream&& operator<<(HobotLogNullOStream&& out,
                                      uint16_t content);
HLOG HobotLogNullOStream&& operator<<(HobotLogNullOStream&& out,
                                      int32_t content);
HLOG HobotLogNullOStream&& operator<<(HobotLogNullOStream&& out,
                                      uint32_t content);
HLOG HobotLogNullOStream&& operator<<(HobotLogNullOStream&& out,
                                      int64_t content);
HLOG HobotLogNullOStream&& operator<<(HobotLogNullOStream&& out,
                                      uint64_t content);
HLOG HobotLogNullOStream&& operator<<(HobotLogNullOStream&& out, float content);
HLOG HobotLogNullOStream&& operator<<(HobotLogNullOStream&& out,
                                      double content);

}  // namespace hlog
}  // namespace hobot

#endif  // HLOG_HOBOT_LOG_NULL_OSTREAM_H_
