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

#ifndef _MSG_POOL_H_
#define _MSG_POOL_H_

#include <algorithm>
#include <condition_variable>
#include <list>
#include <memory>
#include <mutex>
#include <queue>
#include <utility>

namespace hobot {
namespace easy_dnn {

template <typename T>
class Pool {
 public:
  /**
   * Create a pool instance
   * @tparam Args
   * @param[in] pre_alloc_cnt pre-allocate item count
   * @param[in] max_alloc_cnt max allocate item count allowed
   * @param[in] args constructor arguments
   * @return pool instance
   */
  template <typename... Args>
  static std::shared_ptr<Pool<T>> Create(int32_t pre_alloc_cnt,
                                         int32_t max_alloc_cnt,
                                         Args &&... args) {
    auto *pool = new Pool<T>();
    pool->Init(pre_alloc_cnt, max_alloc_cnt, std::forward<Args>(args)...);
    return std::shared_ptr<Pool<T>>(pool);
  }

  /**
   * Get one item from pool
   * @return item if pool not empty, null otherwise
   */
  T *Get() {
    std::lock_guard<std::mutex> lck{mutex_};
    if (free_list_.empty()) {
      return nullptr;
    }
    T *item = free_list_.front();
    free_list_.pop();
    return item;
  }

  /**
   * Get one item from pool
   * @param[in] timeout
   * @return item if pool not empty, null otherwise
   */
  T *Get(int32_t timeout) {
    std::unique_lock<std::mutex> lck{mutex_};
    if (timeout > 0) {
      cv_.wait_for(lck, std::chrono::milliseconds(timeout), [this] {
        return !this->free_list_.empty();
      });
    } else {
      cv_.wait(lck, [this] { return !this->free_list_.empty(); });
    }

    if (free_list_.empty()) {
      return nullptr;
    }

    T *item = free_list_.front();
    free_list_.pop();
    return item;
  }

  /**
   * Get one item from pool, create a new item if pool is empty and
   *    total item count is within the limit of `max_alloc_cnt`
   * @tparam Args
   * @param[in] timeout
   * @param[in] args
   * @return item if success, null otherwise
   */
  template <typename... Args>
  T *GetEx(int32_t timeout, Args &&... args) {
    std::unique_lock<std::mutex> lck{mutex_};
    if (free_list_.empty() && items_.size() < max_alloc_cnt_) {
      AllocItem(std::forward<Args>(args)...);
    }

    if (timeout > 0) {
      cv_.wait_for(lck, std::chrono::milliseconds(timeout), [this] {
        return !this->free_list_.empty();
      });
    } else {
      cv_.wait(lck, [this] { return !this->free_list_.empty(); });
    }

    if (free_list_.empty()) {
      return nullptr;
    }

    auto *item = free_list_.front();
    free_list_.pop();
    return item;
  }

  /**
   *
   * @return std::shared_ptr<T>
   */
  std::shared_ptr<T> GetSharedPtr() { return WrapItem(Get(), true); }

  /**
   *
   * @param[in] timeout
   * @return std::shared_ptr<T>
   */
  std::shared_ptr<T> GetSharedPtr(int32_t timeout) {
    return WrapItem(Get(timeout), true);
  }

  /**
   *
   * @tparam Args
   * @param[in] args
   * @return std::shared_ptr<T>
   */
  template <typename... Args>
  std::shared_ptr<T> GetSharedPtrEx(int32_t timeout, Args &&... args) {
    return WrapItem(GetEx(timeout, std::forward<Args>(args)...), true);
  }

  /**
   * Adjust max allocate item allowed count,
   *    and surplus items will be destroyed immediately if available
   * @param[in] max_alloc_cnt
   */
  void Resize(int32_t max_alloc_cnt) {
    std::lock_guard<std::mutex> lck{mutex_};
    max_alloc_cnt_ = max_alloc_cnt <= 0 ? INT32_MAX : max_alloc_cnt;
    while (items_.size() > max_alloc_cnt_ && !free_list_.empty()) {
      auto item = free_list_.front();
      free_list_.pop();
      Remove(item);
    }
  }

  /**
   * ReleaseTensor item, recycle to pool
   * @param[in] item
   */
  void Release(T *item) {
    item->Reset();
    {
      std::unique_lock<std::mutex> lck{mutex_};
      if (items_.size() > max_alloc_cnt_) {
        // destroy surplus item
        Remove(item);
      } else {
        free_list_.push(item);
      }
    }
    cv_.notify_all();
  }

  ~Pool() {
    std::lock_guard<std::mutex> lck{mutex_};
    for (auto *item : items_) {
      delete item;
    }
    items_.clear();
    while (!free_list_.empty()) {
      free_list_.pop();
    }
  }

 private:
  /**
   * Initialize pool, pre-allocate items if necessary
   * @tparam Args
   * @param[in] pre_alloc_cnt
   * @param[in] max_alloc_cnt
   * @param[in] args
   * @return 0
   */
  template <typename... Args>
  int32_t Init(int32_t pre_alloc_cnt, int32_t max_alloc_cnt, Args &&... args) {
    max_alloc_cnt_ = max_alloc_cnt <= 0 ? INT32_MAX : max_alloc_cnt;
    for (int32_t i = 0; i < std::min(pre_alloc_cnt, (int32_t)max_alloc_cnt_);
         i++) {
      AllocItem(std::forward<Args>(args)...);
    }
    return 0;
  }

  void Remove(T *item) {
    auto it = std::find(items_.begin(), items_.end(), item);
    items_.erase(it);
    delete item;
  }

  template <typename... Args>
  int32_t AllocItem(Args &&... args) {
    T *item = new T(std::forward<Args>(args)...);
    items_.push_back(item);
    free_list_.push(item);
    return 0;
  }

 private:
  std::shared_ptr<T> WrapItem(T *item, bool auto_release) {
    if (!item) {
      return nullptr;
    }
    if (auto_release) {
      return std::shared_ptr<T>(item, [this](T *item) { this->Release(item); });
    } else {
      return std::shared_ptr<T>(item, [](T *item) {});
    }
  }

 private:
  std::mutex mutex_;
  std::condition_variable cv_;
  std::list<T *> items_;
  std::queue<T *> free_list_;
  uint32_t max_alloc_cnt_ = 0;
};

}  // namespace easy_dnn
}  // namespace hobot

#endif  // _MSG_POOL_H_
