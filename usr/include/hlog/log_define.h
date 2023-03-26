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

#ifndef HLOG_LOG_DEFINE_H_
#define HLOG_LOG_DEFINE_H_

#include <string>

#if defined(_MSC_VER)
#ifdef HLOG_DLL
#ifdef HLOG_LIB
#define HLOG __declspec(dllexport)
#else
#define HLOG __declspec(dllimport)
#endif
#else
#define HLOG
#endif
#elif defined(__GNUC__)
#ifdef HLOG_LIB
#define HLOG __attribute__((visibility("default")))
#else
#define HLOG
#endif
#endif

namespace hobot {
namespace hlog {
enum HLOG LogLevel {
  log_trace = 0,
  log_debug,
  log_info,
  log_warn,
  log_err,
  log_critical
};

struct HLOG LogProperty {
 public:
  LogLevel level;
  std::string tag;
  std::string save_path;
  std::string log_file_name;
  bool is_rotate;
  unsigned int file_size;
  unsigned int file_count;
  bool is_async;
  bool is_async_block;
  unsigned int async_max_item;
  unsigned int async_max_thread;

  LogProperty()
    : level(log_err),
      log_file_name("test.log"),
      is_rotate(false),
      file_size(2 * 1024 * 1024),
      file_count(24),
      is_async(true),
      is_async_block(false),
      async_max_item(8192),
      async_max_thread(1) {}
};
}  // namespace hlog
}  // namespace hobot
#endif  // HLOG_LOG_DEFINE_H_
