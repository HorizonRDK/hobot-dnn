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

#ifndef HLOG_HOBOT_LOG_BUFFER_BLOCK_H_
#define HLOG_HOBOT_LOG_BUFFER_BLOCK_H_

#include <hlog/log_define.h>

#include <condition_variable>
#include <iostream>
#include <memory>
#include <mutex>
#include <string>
#include <thread>
#include <atomic>

namespace hobot {
namespace hlog {
enum ABBlock {
  ABBlock_None = 0,
  ABBlock_A,
  ABBlock_B,
  ABBlock_Count
};

enum BufferStatus {
  Buffer_Using = 1,  // Buffer is using now.
  Buffer_Full,  // Buffer is full, need to send.
  Buffer_Idle,  // Buffer block is idle.
  Buffer_Invalied,  // Buffer can not used.
  Buffer_Count  //  Invalied argument.
};

class BufferBlock {
 public:
  explicit BufferBlock(uint32_t buffer_size);
  ~BufferBlock();
  bool Write(const std::string& data);
  size_t Size();
  const BufferStatus Status();
  void Reset();
  void Copy(std::string& str);

  const uint32_t buffer_size_{0};

 private:
  std::string buffer_{""};
  std::mutex read_mutex_;
  BufferStatus buffer_status_{Buffer_Invalied};
};

class BlockManager;
class HLOG BasicSender {
 public:
  BasicSender() {}
  virtual bool Init() { return false; }
  virtual void SendLog(const std::string& log_data) {}
  virtual bool Avaliable() { return false; }
};

class HLOG BlockManager {
 public:
  static BlockManager* GetInstance();
  void Init(std::shared_ptr<BasicSender> sender);
  bool StoreLog(const std::string& log);
  ~BlockManager();

 private:
  BlockManager();
  void RunWrap();

  BufferBlock* buffer_block_A_{nullptr};
  BufferBlock* buffer_block_B_{nullptr};
  std::shared_ptr<std::thread> send_thread_{nullptr};
  std::shared_ptr<BasicSender> sender_{nullptr};
  ABBlock ab_avaliable_{ABBlock_None};
  std::atomic_bool avaliable_{false};
  std::mutex send_mutex_;
  std::condition_variable send_condition_;
};

}  // namespace hlog
}  // namespace hobot

#endif  // HLOG_HOBOT_LOG_BUFFER_BLOCK_H_
