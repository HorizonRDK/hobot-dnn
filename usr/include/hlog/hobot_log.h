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

#ifndef HLOG_HOBOT_LOG_H_
#define HLOG_HOBOT_LOG_H_

#include <hlog/log_define.h>

#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <atomic>

namespace hobot {
namespace hlog {
HLOG void AddOne(uint32_t* value);
HLOG void SubN(uint32_t* value, int n);
HLOG void HLOG_EXCCEPTION_OUTPUT();

template <typename Head, typename... Args>
void HLOG_EXCCEPTION_OUTPUT(const Head& head, const Args&... args) {
  std::cout << head << " ";
  HLOG_EXCCEPTION_OUTPUT(args...);
}

class BlockManager;
class HLOG HobotLog {
 public:
  void Init(const LogProperty& prop, bool use_sender = false);
  void PrintLog(const char* file, int&& line, hobot::hlog::LogLevel&& level,
                const std::string& str);

  static HobotLog& Instance();
  ~HobotLog();
  static LogLevel level_();

 private:
  HobotLog() = default;
  BlockManager* block_manager_{nullptr};
  std::atomic<bool> log_off_{false};
  static LogLevel global_level_;
};
}  // namespace hlog
}  // namespace hobot

#endif  // HLOG_HOBOT_LOG_H_
