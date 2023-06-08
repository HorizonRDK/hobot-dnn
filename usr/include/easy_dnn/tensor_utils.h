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

#ifndef _EASY_DNN_TENSOR_UTILS_H_
#define _EASY_DNN_TENSOR_UTILS_H_

#include <memory>
#include <vector>

#include "easy_dnn/data_structure.h"

namespace hobot {
namespace easy_dnn {
class TensorUtils {
 public:
  /**
   * Alloc BPU tensor
   * @param[in] properties
   * @param[in] is_pad_data
   * @param[out] tensor
   * @param[out] data_addr
   * @param[out] mem_size
   * @return 0 if success, return defined error code otherwise
   */
  static int32_t AllocateTensor(std::shared_ptr<DNNTensor> &tensor,
                                std::vector<void *> &data_addr,
                                std::vector<int32_t> &mem_size,
                                hbDNNTensorProperties &properties,
                                bool const &is_pad_data = false);

  /**
   * Flush BPU tensor
   * @param[in] tensor
   * @param[in] flag
   * flag : HB_SYS_MEM_CACHE_INVALIDATE (1), use when BPU write done. CPU read
   * from DDR directly.
   * flag : HB_SYS_MEM_CACHE_CLEAN (2), use before BPU read.
   * Flush CPU cache data to DDR.
   * @return 0 if success, return defined error code otherwise
   */
  static int32_t FlushTensor(std::shared_ptr<DNNTensor> &tensor, int32_t flag);
};

}  // namespace easy_dnn
}  // namespace hobot

#endif  // _EASY_DNN_TENSOR_UTILS_H_
