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

#ifndef HLOG_LOGGING_H_
#define HLOG_LOGGING_H_

#define GOOGLE_STATIC

#include <fmt/format.h>

#include <string>
#include <typeinfo>
#include <exception>

#include "hlog/hobot_log.h"
#include "hlog/hobot_log_null_ostream.h"
#include "hlog/hobot_log_ostream.h"

#ifdef HLOG_DEBUG_OFF_
#define HLOGINIT
#define HLOG_T(...)
#define HLOG_D(...)
#define HLOG_I(...)
#define HLOG_W(...)
#define HLOG_E(...)
#define HLOG_C(...)
#define HTLOG_T(SUBTAG, FMT)
#define HTLOG_D(SUBTAG, FMT)
#define HTLOG_I(SUBTAG, FMT)
#define HTLOG_W(SUBTAG, FMT)
#define HTLOG_E(SUBTAG, FMT)
#define HTLOG_C(SUBTAG, FMT)

#define HSLOG_C \
  hobot::hlog::HobotLogNullOStream(__FILE__, __LINE__, \
                                   hobot::hlog::log_critical)
#define HSLOG_E \
  hobot::hlog::HobotLogNullOStream(__FILE__, __LINE__, hobot::hlog::log_err)
#define HSLOG_W \
  hobot::hlog::HobotLogNullOStream(__FILE__, __LINE__, hobot::hlog::log_warn)
#define HSLOG_I \
  hobot::hlog::HobotLogNullOStream(__FILE__, __LINE__, hobot::hlog::log_info)
#define HSLOG_D \
  hobot::hlog::HobotLogNullOStream(__FILE__, __LINE__, hobot::hlog::log_debug)
#define HSLOG_T \
  hobot::hlog::HobotLogNullOStream(__FILE__, __LINE__, hobot::hlog::log_trace)
#else  // ifdef HLOG_DEBUG_OFF_
#define HLOGINIT hobot::hlog::HobotLog::Instance().Init

#define HLOG_T(...)                                                 \
  try {                                                             \
    (hobot::hlog::log_trace >= hobot::hlog::HobotLog::level_()) ?   \
    hobot::hlog::HobotLog::Instance().PrintLog(                     \
      __FILE__, __LINE__, hobot::hlog::log_trace,                   \
      fmt::format(__VA_ARGS__))  : (void) 0;                        \
  } catch(std::exception& e) {                                      \
    std::cout << "[EXCEPTION] origin: ";                            \
    hobot::hlog::HLOG_EXCCEPTION_OUTPUT(__VA_ARGS__);               \
    std::cout << "[EXCEPTION] reason: " << e.what() << std::endl;   \
    std::cout << "[EXCEPTION] position: "                           \
              << __FILE__ << " " << __LINE__ << std::endl;          \
  }

#define HLOG_D(...)                                                 \
  try {                                                             \
    (hobot::hlog::log_debug >= hobot::hlog::HobotLog::level_()) ?   \
    hobot::hlog::HobotLog::Instance().PrintLog(                     \
      __FILE__, __LINE__, hobot::hlog::log_debug,                   \
      fmt::format(__VA_ARGS__)) : (void) 0;                         \
  } catch(std::exception& e) {                                      \
    std::cout << "[EXCEPTION] origin: ";                            \
    hobot::hlog::HLOG_EXCCEPTION_OUTPUT(__VA_ARGS__);               \
    std::cout << "[EXCEPTION] reason: " << e.what() << std::endl;   \
    std::cout << "[EXCEPTION] position: "                           \
              << __FILE__ << " " << __LINE__ << std::endl;          \
  }

#define HLOG_I(...)                                                 \
  try {                                                             \
    (hobot::hlog::log_info >= hobot::hlog::HobotLog::level_()) ?    \
    hobot::hlog::HobotLog::Instance().PrintLog(                     \
      __FILE__, __LINE__, hobot::hlog::log_info,                    \
      fmt::format(__VA_ARGS__))  : (void) 0;                        \
  } catch(std::exception& e) {                                      \
    std::cout << "[EXCEPTION] origin: ";                            \
    hobot::hlog::HLOG_EXCCEPTION_OUTPUT(__VA_ARGS__);               \
    std::cout << "[EXCEPTION] reason: " << e.what() << std::endl;   \
    std::cout << "[EXCEPTION] position: "                           \
              << __FILE__ << " " << __LINE__ << std::endl;          \
  }

#define HLOG_W(...)                                                 \
  try {                                                             \
    (hobot::hlog::log_warn >= hobot::hlog::HobotLog::level_()) ?    \
    hobot::hlog::HobotLog::Instance().PrintLog(                     \
      __FILE__, __LINE__, hobot::hlog::log_warn,                    \
      fmt::format(__VA_ARGS__)) : (void) 0;                         \
  } catch(std::exception& e) {                                      \
    std::cout << "[EXCEPTION] origin: ";                            \
    hobot::hlog::HLOG_EXCCEPTION_OUTPUT(__VA_ARGS__);               \
    std::cout << "[EXCEPTION] reason: " << e.what() << std::endl;   \
    std::cout << "[EXCEPTION] position: "                           \
              << __FILE__ << " " << __LINE__ << std::endl;          \
  }

#define HLOG_E(...)                                                 \
  try {                                                             \
    (hobot::hlog::log_err >= hobot::hlog::HobotLog::level_()) ?     \
    hobot::hlog::HobotLog::Instance().PrintLog(                     \
      __FILE__, __LINE__, hobot::hlog::log_err,                     \
      fmt::format(__VA_ARGS__)) : (void) 0;                         \
  } catch(std::exception& e) {                                      \
    std::cout << "[EXCEPTION] origin: ";                            \
    hobot::hlog::HLOG_EXCCEPTION_OUTPUT(__VA_ARGS__);               \
    std::cout << "[EXCEPTION] reason: " << e.what() << std::endl;   \
    std::cout << "[EXCEPTION] position: "                           \
              << __FILE__ << " " << __LINE__ << std::endl;          \
  }

#define HLOG_C(...)                                                 \
  try {                                                             \
    (hobot::hlog::log_critical >= hobot::hlog::HobotLog::level_()) ? \
    hobot::hlog::HobotLog::Instance().PrintLog(                     \
      __FILE__, __LINE__, hobot::hlog::log_critical,                \
      fmt::format(__VA_ARGS__)) : (void) 0;                         \
  } catch(std::exception& e) {                                      \
    std::cout << "[EXCEPTION] origin: ";                            \
    hobot::hlog::HLOG_EXCCEPTION_OUTPUT(__VA_ARGS__);               \
    std::cout << "[EXCEPTION] reason: " << e.what() << std::endl;   \
    std::cout << "[EXCEPTION] position: "                           \
              << __FILE__ << " " << __LINE__ << std::endl;          \
  }

#define HTLOG_T(SUBTAG, FMT, ...)                                   \
  try {                                                             \
    (hobot::hlog::log_trace >= hobot::hlog::HobotLog::level_()) ?   \
    hobot::hlog::HobotLog::Instance().PrintLog(                     \
      __FILE__, __LINE__, hobot::hlog::log_trace,                   \
      fmt::format("[{}]{}", SUBTAG,                                 \
      fmt::format(FMT, ##__VA_ARGS__))) : (void) 0;                 \
  } catch(std::exception& e) {                                      \
    std::cout << "[EXCEPTION] origin: " << SUBTAG << " " << FMT;    \
    hobot::hlog::HLOG_EXCCEPTION_OUTPUT(__VA_ARGS__);               \
    std::cout << "[EXCEPTION] reason: " << e.what() << std::endl;   \
    std::cout << "[EXCEPTION] position: "                           \
              << __FILE__ << " " << __LINE__ << std::endl;          \
  }

#define HTLOG_D(SUBTAG, FMT, ...)                                   \
  try {                                                             \
    (hobot::hlog::log_debug >= hobot::hlog::HobotLog::level_()) ?   \
    hobot::hlog::HobotLog::Instance().PrintLog(                     \
      __FILE__, __LINE__, hobot::hlog::log_debug,                   \
      fmt::format("[{}]{}", SUBTAG,                                 \
      fmt::format(FMT, ##__VA_ARGS__))) : (void) 0;                 \
  } catch(std::exception& e) {                                      \
    std::cout << "[EXCEPTION] origin: " << SUBTAG << " " << FMT;    \
    hobot::hlog::HLOG_EXCCEPTION_OUTPUT(__VA_ARGS__);               \
    std::cout << "[EXCEPTION] reason: " << e.what() << std::endl;   \
    std::cout << "[EXCEPTION] position: "                           \
              << __FILE__ << " " << __LINE__ << std::endl;          \
  }

#define HTLOG_I(SUBTAG, FMT, ...)                                   \
  try {                                                             \
    (hobot::hlog::log_info >= hobot::hlog::HobotLog::level_()) ?    \
    hobot::hlog::HobotLog::Instance().PrintLog(                     \
      __FILE__, __LINE__, hobot::hlog::log_info,                    \
      fmt::format("[{}]{}", SUBTAG,                                 \
      fmt::format(FMT, ##__VA_ARGS__))) : (void) 0;                 \
  } catch(std::exception& e) {                                      \
    std::cout << "[EXCEPTION] origin: " << SUBTAG << " " << FMT;    \
    hobot::hlog::HLOG_EXCCEPTION_OUTPUT(__VA_ARGS__);               \
    std::cout << "[EXCEPTION] reason: " << e.what() << std::endl;   \
    std::cout << "[EXCEPTION] position: "                           \
              << __FILE__ << " " << __LINE__ << std::endl;          \
  }

#define HTLOG_W(SUBTAG, FMT, ...)                                   \
  try {                                                             \
    (hobot::hlog::log_warn >= hobot::hlog::HobotLog::level_()) ?    \
    hobot::hlog::HobotLog::Instance().PrintLog(                     \
      __FILE__, __LINE__, hobot::hlog::log_warn,                    \
      fmt::format("[{}]{}", SUBTAG,                                 \
      fmt::format(FMT, ##__VA_ARGS__))) : (void) 0;                 \
  } catch(std::exception& e) {                                      \
    std::cout << "[EXCEPTION] origin: " << SUBTAG << " " << FMT;    \
    hobot::hlog::HLOG_EXCCEPTION_OUTPUT(__VA_ARGS__);               \
    std::cout << "[EXCEPTION] reason: " << e.what() << std::endl;   \
    std::cout << "[EXCEPTION] position: "                           \
              << __FILE__ << " " << __LINE__ << std::endl;          \
  }

#define HTLOG_E(SUBTAG, FMT, ...)                                   \
  try {                                                             \
    (hobot::hlog::log_err >= hobot::hlog::HobotLog::level_()) ?     \
    hobot::hlog::HobotLog::Instance().PrintLog(                     \
      __FILE__, __LINE__, hobot::hlog::log_err,                     \
      fmt::format("[{}]{}", SUBTAG,                                 \
      fmt::format(FMT, ##__VA_ARGS__))) : (void) 0;                 \
  } catch(std::exception& e) {                                      \
    std::cout << "[EXCEPTION] origin: " << SUBTAG << " " << FMT;    \
    hobot::hlog::HLOG_EXCCEPTION_OUTPUT(__VA_ARGS__);               \
    std::cout << "[EXCEPTION] reason: " << e.what() << std::endl;   \
    std::cout << "[EXCEPTION] position: "                           \
              << __FILE__ << " " << __LINE__ << std::endl;          \
  }

#define HTLOG_C(SUBTAG, FMT, ...)                                   \
  try {                                                             \
    (hobot::hlog::log_critical >= hobot::hlog::HobotLog::level_()) ? \
    hobot::hlog::HobotLog::Instance().PrintLog(                     \
      __FILE__, __LINE__, hobot::hlog::log_critical,                \
      fmt::format("[{}]{}", SUBTAG,                                 \
      fmt::format(FMT, ##__VA_ARGS__))) : (void) 0;                 \
  } catch(std::exception& e) {                                      \
    std::cout << "[EXCEPTION] origin: " << SUBTAG << " " << FMT;    \
    hobot::hlog::HLOG_EXCCEPTION_OUTPUT(__VA_ARGS__);               \
    std::cout << "[EXCEPTION] reason: " << e.what() << std::endl;   \
    std::cout << "[EXCEPTION] position: "                           \
              << __FILE__ << " " << __LINE__ << std::endl;          \
  }

#define HSLOG_C                                                     \
  hobot::hlog::HobotLogOstream(__FILE__, __LINE__,                  \
  hobot::hlog::log_critical).stream()
#define HSLOG_E                                                     \
  hobot::hlog::HobotLogOstream(__FILE__, __LINE__,                  \
  hobot::hlog::log_err).stream()
#define HSLOG_W                                                     \
  hobot::hlog::HobotLogOstream(__FILE__, __LINE__,                  \
  hobot::hlog::log_warn).stream()
#define HSLOG_I                                                     \
  hobot::hlog::HobotLogOstream(__FILE__, __LINE__,                  \
  hobot::hlog::log_info).stream()
#define HSLOG_D                                                     \
  hobot::hlog::HobotLogOstream(__FILE__, __LINE__,                  \
  hobot::hlog::log_debug).stream()
#define HSLOG_T                                                     \
  hobot::hlog::HobotLogOstream(__FILE__, __LINE__,                  \
  hobot::hlog::log_trace).stream()

#define HLOG_CHECK_PRINT(arg1, arg2, comm)                          \
  try {                                                             \
    (hobot::hlog::log_critical >= hobot::hlog::HobotLog::level_()) ? \
    hobot::hlog::HobotLog::Instance().PrintLog(                     \
      __FILE__, __LINE__, hobot::hlog::log_err,                     \
      fmt::format("[{} {} {}]  failed!", #arg1, #comm, #arg2))      \
     : (void) 0;                                                    \
  } catch(std::exception& e) {                                      \
    std::cout << "[EXCEPTION] origin: ";                            \
    hobot::hlog::HLOG_EXCCEPTION_OUTPUT(#arg1, #comm, #arg2);       \
    std::cout << "[EXCEPTION] reason: " << e.what() << std::endl;   \
    std::cout << "[EXCEPTION] position: "                           \
              << __FILE__ << " " << __LINE__ << std::endl;          \
  }

#define HLOG_IF_PRINT(arg, level)                                   \
  (level >= hobot::hlog::HobotLog::level_()) ?                      \
  hobot::hlog::HobotLog::Instance().PrintLog(                       \
    __FILE__, __LINE__, level, arg) : (void) 0;                     \

#define HLOG_EQ(arg1, arg2)                                         \
  if ((arg1) != (arg2)) {                                           \
    HLOG_CHECK_PRINT(arg1, arg2, EQUAL)                             \
  }

#define HLOG_NE(arg1, arg2)                                         \
  if ((arg1) == (arg2)) {                                           \
    HLOG_CHECK_PRINT(arg1, arg2, NOT EQUAL)                         \
  }

#define HLOG_LE(arg1, arg2)                                         \
  if ((arg1) > (arg2)) {                                            \
    HLOG_CHECK_PRINT(arg1, arg2, LESS EQUAL)                        \
  }

#define HLOG_LT(arg1, arg2)                                         \
  if ((arg1) >= (arg2)) {                                           \
    HLOG_CHECK_PRINT(arg1, arg2, LESS THAN)                         \
  }

#define HLOG_GE(arg1, arg2)                                         \
  if ((arg1) < (arg2)) {                                            \
    HLOG_CHECK_PRINT(arg1, arg2, GREATER EQUAL)                     \
  }

#define HLOG_GT(arg1, arg2)                                         \
  if ((arg1) <= (arg2)) {                                           \
    HLOG_CHECK_PRINT(arg1, arg2, GREATER THAN)                      \
  }

#define HLOG_IF(level, condition, arg)                              \
  if (condition) {                                                  \
    HLOG_IF_PRINT(arg, level)                                       \
  }

#define HSLOG_IF(level, condition)                                  \
  static_cast<void>(0),                                             \
  ((level < hobot::hlog::HobotLog::level_()) || !(condition))       \
  ? (void) 0 :                                                      \
  hobot::hlog::LogMessageVoidify() &                                \
  hobot::hlog::HobotLogOstream(__FILE__, __LINE__, level).stream()


#define HLOG_OCCURRENCES occurrence_##__FUNCTION__##__LINE__
#define HLOG_OCCURRENCES_MOD_N occurrence_mode_n##__FUNCTION__##__LINE__

#define HLOG_FIRST_N(n, level, arg)                                 \
  {                                                                 \
    static unsigned HLOG_OCCURRENCES = 0;                            \
    hobot::hlog::AddOne(&HLOG_OCCURRENCES);                         \
    if (HLOG_OCCURRENCES <= n) {                                     \
      try {                                                         \
      (level >= hobot::hlog::HobotLog::level_()) ?                  \
      hobot::hlog::HobotLog::Instance().PrintLog(                   \
        __FILE__, __LINE__, level,                                  \
        fmt::format("[{}]{}", HLOG_OCCURRENCES, arg)) : (void) 0;    \
      } catch(std::exception& e) {                                      \
        std::cout << "[EXCEPTION] origin: ";                            \
        hobot::hlog::HLOG_EXCCEPTION_OUTPUT(HLOG_OCCURRENCES, arg);     \
        std::cout << "[EXCEPTION] reason: " << e.what() << std::endl;   \
        std::cout << "[EXCEPTION] position: "                           \
                  << __FILE__ << " " << __LINE__ << std::endl;          \
      }                                                             \
    }                                                               \
  }

#define HLOG_ONCE(level, arg)                                       \
  HLOG_FIRST_N(1, level, arg)

#define HLOG_EVERY_N(n, level, arg)                                 \
  {                                                                 \
    static unsigned HLOG_OCCURRENCES = 0, HLOG_OCCURRENCES_MOD_N = 0; \
    hobot::hlog::AddOne(&HLOG_OCCURRENCES);                         \
    hobot::hlog::AddOne(&HLOG_OCCURRENCES_MOD_N);                   \
    if (HLOG_OCCURRENCES_MOD_N > n) {                                \
      hobot::hlog::SubN(&HLOG_OCCURRENCES_MOD_N, n);                \
    }                                                               \
    if (HLOG_OCCURRENCES_MOD_N == 1) {                               \
      try {                                                         \
        (level >= hobot::hlog::HobotLog::level_()) ?                \
        hobot::hlog::HobotLog::Instance().PrintLog(                 \
          __FILE__, __LINE__, level,                                \
          fmt::format("[{}]{}", HLOG_OCCURRENCES, arg)) : (void) 0;  \
      } catch(std::exception& e) {                                      \
        std::cout << "[EXCEPTION] origin: ";                            \
        hobot::hlog::HLOG_EXCCEPTION_OUTPUT(HLOG_OCCURRENCES, arg);     \
        std::cout << "[EXCEPTION] reason: " << e.what() << std::endl;   \
        std::cout << "[EXCEPTION] position: "                           \
                  << __FILE__ << " " << __LINE__ << std::endl;          \
      }                                                             \
    }                                                               \
  }
#endif  // ifdef HLOG_DEBUG_OFF_
#endif  // HLOG_LOGGING_H_
