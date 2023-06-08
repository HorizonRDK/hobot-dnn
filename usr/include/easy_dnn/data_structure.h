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

#ifndef _EASY_DNN_DATA_STRUCTURE_H_
#define _EASY_DNN_DATA_STRUCTURE_H_

#include <climits>
#include <memory>
#include <ostream>
#include <string>

#include "any_utils.h"
#include "dnn/hb_dnn.h"

#define DNN_RESULT_KEY "dnn_result"

namespace hobot {
namespace easy_dnn {

using ResultMap = AnyMap;

class DNNInput {
 public:
  virtual void Reset() {}
  virtual ~DNNInput() = default;
};

class NV12PyramidInput : public DNNInput {
 public:
  uint64_t y_phy_addr;
  void *y_vir_addr;
  uint64_t uv_phy_addr;
  void *uv_vir_addr;
  int32_t height;
  int32_t width;
  int32_t y_stride;
  int32_t uv_stride;
  void Reset() override {}
};

class DNNResult {
 public:
  virtual void Reset() {}
  virtual ~DNNResult() = default;
  virtual void Print(std::ostream &os) const {}

  friend std::ostream &operator<<(std::ostream &os, DNNResult const &result) {
    result.Print(os);
    return os;
  }

  /**
   * Get result by default DNN_RESULT_KEY
   * @param[out] result
   */
  template <typename ResultType>
  int32_t GetResult(ResultType &result) {
    return results_.GetValue(result, DNN_RESULT_KEY);
  }

  /**
   * Set result by default DNN_RESULT_KEY
   * @param[in] result
   */
  template <typename ResultType>
  int32_t SetResult(ResultType const &result) {
    return results_.SetValue(DNN_RESULT_KEY, result);
  }

  /**
   * Get result by key
   * @param[in] key
   * @param[out] result
   */
  template <typename ResultType>
  int32_t GetResult(ResultType &result, std::string const &key) {
    return results_.GetValue(result, key);
  }

  /**
   * Set result by key
   * @param[in] key
   * @param[in] result
   */
  template <typename ResultType>
  int32_t SetResult(std::string const &key, ResultType const &result) {
    return results_.SetValue(key, result);
  }

 private:
  ResultMap results_;
};

class DNNTensor : public hbDNNTensor {
 public:
  DNNTensor() : hbDNNTensor() {}
  virtual void Reset() {}
  virtual ~DNNTensor() = default;
};

class DNNInferCtrlParam : public hbDNNInferCtrlParam {
 public:
  DNNInferCtrlParam() : hbDNNInferCtrlParam() {
    HB_DNN_INITIALIZE_INFER_CTRL_PARAM(this);
  }
};

struct Profiler {
  int32_t max_time{INT_MIN};
  int32_t min_time{INT_MAX};
  int32_t avg_time{0};
  int32_t latest_time{0};
  uint64_t frame_count{0U};
  friend std::ostream &operator<<(std::ostream &os, Profiler p) {
    os << "max time: " << p.max_time << ", min time: " << p.min_time
       << ", average time: " << p.avg_time << ", latest time: " << p.latest_time
       << ", frame_count: " << p.frame_count << std::endl;
    return os;
  }
};

}  // namespace easy_dnn
}  // namespace hobot

#endif  // _EASY_DNN_DATA_STRUCTURE_H_
