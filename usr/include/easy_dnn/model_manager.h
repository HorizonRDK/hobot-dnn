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

#ifndef _EASY_DNN_MODEL_MANAGER_IMPL_H_
#define _EASY_DNN_MODEL_MANAGER_IMPL_H_

#include <functional>
#include <string>
#include <utility>
#include <vector>

namespace hobot {
namespace easy_dnn {

class Model;

using QueryFilter = std::function<bool(Model* model)>;

extern QueryFilter QueryByModelName(const std::string& model_name);

class ModelManager {
 public:
  /**
   * Get singleton instance
   * @return instance
   */
  static ModelManager* GetInstance();

  /**
   * Load model
   * @param[out] models
   * @param[in] model_files
   * @return 0 if success, return defined error code otherwise
   */
  virtual int32_t Load(std::vector<Model*>& models,
                       const std::vector<std::string>& model_files) = 0;

  /**
   * Load model
   * @param[out] models
   * @param[in] model_file
   * @return 0 if success, return defined error code otherwise
   */
  virtual int32_t Load(std::vector<Model*>& models,
                       const std::string& model_file) = 0;

  /**
   * Load model
   * @param[out] models
   * @param[in] models_data
   * @return 0 if success, return defined error code otherwise
   */
  virtual int32_t Load(
      std::vector<Model*>& models,
      const std::vector<std::pair<const void*, int32_t>>& models_data) = 0;

  /**
   * Load model from single ddr
   * @param[out] models
   * @param[in] model_data
   * @return 0 if success, return defined error code otherwise
   */
  virtual int32_t Load(std::vector<Model*>& models,
                       std::pair<const void*, int32_t>& model_data) = 0;

  /**
   * Get all loaded models
   * @return all loaded model
   */
  virtual std::vector<Model*> GetModels() = 0;

  /**
   * Get models by filter
   * @param[in] filter
   * @return
   */
  virtual std::vector<Model*> GetModels(QueryFilter filter) = 0;

  /**
   * Get model by filter, return the first matched model
   * @param[in] filter
   * @return
   */
  virtual Model* GetModel(QueryFilter filter) = 0;

  /**
   * Offload models
   * @param[in] models
   * @return 0 if success, return defined error code otherwise
   */
  virtual int32_t OffLoad(std::vector<Model*>& models) = 0;

  /**
   * Offload model
   * @param[in] model
   * @return 0 if success, return defined error code otherwise
   */
  virtual int32_t OffLoad(Model* model) = 0;

  virtual ~ModelManager() = default;
};

}  // namespace easy_dnn
}  // namespace hobot

#endif  // _EASY_DNN_MODEL_MANAGER_IMPL_H_
