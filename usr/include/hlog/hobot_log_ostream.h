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

#ifndef HLOG_HOBOT_LOG_OSTREAM_H_
#define HLOG_HOBOT_LOG_OSTREAM_H_

#include <iostream>
#include <string>

#include "hlog/log_define.h"

namespace hobot {
namespace hlog {
// This class is used to explicitly ignore values in the conditional
// logging macros.  This avoids compiler warnings like "value computed
// is not used" and "statement has no effect".
class LogMessageVoidify {
 public:
  LogMessageVoidify() { }
  // This has to be an operator with a precedence lower than << but
  // higher than ?:
  void operator&(std::ostream&) { }
};

class HLOG HobotLogOstream {
 public:
  class LogStreamBuf : public std::streambuf {
   public:
    // REQUIREMENTS: "len" must be >= 2 to account for the '\n' and '\0'.
    LogStreamBuf(char *buf, int len) {
      setp(buf, buf + len - 2);
    }
    // This effectively ignores overflow.
    int_type overflow(int_type ch) {
      return ch;
    }
    // Legacy public ostrstream method.
    size_t pcount() const { return pptr() - pbase(); }
    char* pbase() const { return std::streambuf::pbase(); }
  };

  class LogStream : public std::ostream {
   public:
    LogStream(char *buf, int len)
        : std::ostream(NULL)
        , streambuf_(buf, len) {
      rdbuf(&streambuf_);
    }
    // Legacy std::streambuf methods.
    size_t pcount() const { return streambuf_.pcount(); }
    char* pbase() const { return streambuf_.pbase(); }
    char* str() const { return pbase(); }
   private:
    LogStream(const LogStream&);
    LogStream& operator=(const LogStream&);
    LogStreamBuf streambuf_;
  };

 public:
  HobotLogOstream(const char* file, const uint64_t line,
                  hobot::hlog::LogLevel level, bool condition = true);
  virtual ~HobotLogOstream();
  std::ostream& stream();

 private:
  static const size_t kMaxLogMessageLen;
  const char* file_;
  const uint64_t line_;
  hobot::hlog::LogLevel level_;
  const bool condition_;
  char* message_text_;
  LogStream* stream_;
};
}  // namespace hlog
}  // namespace hobot

#endif  // HLOG_HOBOT_LOG_OSTREAM_H_
