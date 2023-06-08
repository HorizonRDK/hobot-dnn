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

#ifndef _EASY_DNN_TASK_H_
#define _EASY_DNN_TASK_H_
#include <memory>
#include <string>
#include <vector>

#include "dnn/hb_dnn.h"

namespace hobot {
namespace easy_dnn {

class DNNInferCtrlParam;
class Model;
class InputDescription;
class OutputDescription;
class DNNInput;
class DNNResult;
class DNNTensor;

class Task {
 public:
  /**
   * Set task control param, include set core id, priority etc.
   * @param[in] ctrl_param
   */
  virtual int32_t SetCtrlParam(DNNInferCtrlParam &ctrl_param) = 0;

  /**
   * Process input according to input description information
   * @return 0 if success, return defined error code otherwise
   */
  virtual int32_t ProcessInput() = 0;

  /**
   * Get estimate inference time. It consists of two periods， pending time
   *    (period from submission to execution) and execute time (period from
   *    execution to finish), depends on task control param,
   *    and rois(for ModelRoiInferTask)
   * @param[out] estimate_infer_time, time of us.
   * @param[in] ctrl_param
   * @return 0 if success, return defined error code otherwise
   */
  virtual int32_t GetEstimateInferTime(int32_t &estimate_infer_time,
                                       DNNInferCtrlParam &ctrl_param) = 0;

  /**
   * Run task
   * @return 0 if success, return defined error code otherwise
   */
  virtual int32_t RunInfer() = 0;

  /**
   * Wait task infer done
   * @param[in] timeout, timeout of ms
   * @return 0 if success, return defined error code otherwise
   */
  virtual int32_t WaitInferDone(int32_t timeout) = 0;

  /**
   * Parse output according to output description information
   * @return 0 if success, return defined error code otherwise
   */
  virtual int32_t ParseOutput() = 0;

  /**
   * Count the time of the process of running task
   * @param[out] execute_time, time of us.
   * @return 0 if success, return defined error code otherwise
   */
  virtual int32_t GetExecuteTime(int32_t &execute_time) = 0;

  /**
   * Indicate all outputs have been retridved, the task is ready for set
   * in/output, run inference etc again.
   * @return 0 if success, return defined error code otherwise
   */
  virtual int32_t GetOutputsDone() = 0;

  /**
   * Terminate current task, release task resource in proper time
   * @return 0 if success, return defined error code otherwise
   * */
  virtual int32_t Terminate() = 0;

  virtual ~Task() = default;
};

class ModelTask : public Task {
 public:
  /**
   * Set model
   * @param[in] model
   * @return 0 if success, return defined error code otherwise
   */
  virtual int32_t SetModel(Model *model) = 0;

  /**
   * Get model
   * @return model if set, return nullptr otherwise
   */
  virtual Model *GetModel() = 0;

  /**
   * set one input description
   * @param[in] input_desc
   * @return 0 if success, return defined error code otherwise
   */
  virtual int32_t SetInputDescription(
      std::shared_ptr<InputDescription> &input_desc) = 0;

  /**
   * set input descriptions
   * @param[in] input_descs
   * @return 0 if success, return defined error code otherwise
   */
  virtual int32_t SetInputDescriptions(
      std::vector<std::shared_ptr<InputDescription>> &input_descs) = 0;

  /**
   * Get input description
   * @param[out] input_desc
   * @param[in] input_index
   * @return 0 if success, return defined error code otherwise
   */
  virtual int32_t GetInputDescription(
      std::shared_ptr<InputDescription> &input_desc, int32_t input_index) = 0;

  /**
   * Set one output description
   * @param[in] output_desc
   * @return 0 if success, return defined error code otherwise
   */
  virtual int32_t SetOutputDescription(
      std::shared_ptr<OutputDescription> &output_desc) = 0;

  /**
   * Set all output description
   * @param[in] output_descs
   * @return 0 if success, return defined error code otherwise
   */
  virtual int32_t SetOutputDescriptions(
      std::vector<std::shared_ptr<OutputDescription>> &output_descs) = 0;

  /**
   * Get output description
   * @param[out] output_desc
   * @param[in] output_index
   * @return 0 if success, return defined error code otherwise
   */
  virtual int32_t GetOutputDescription(
      std::shared_ptr<OutputDescription> &output_desc,
      int32_t output_index) = 0;
};

class ModelInferTask : virtual public ModelTask {
 public:
  /**
   * Set input
   * @param[in] input_index
   * @param[in] input
   * @return 0 if success, return defined error code otherwise
   */
  virtual int32_t SetInput(int32_t input_index,
                           std::shared_ptr<DNNInput> &input) = 0;

  /**
   *  Set all inputs
   * @param[in] inputs
   * @return 0 if success, return defined error code otherwise
   */
  virtual int32_t SetInputs(std::vector<std::shared_ptr<DNNInput>> &inputs) = 0;

  /**
   * Set one input tensor
   * @param[in] input_index
   * @param[in] input_tensor
   * @return 0 if success, return defined error code otherwise
   */
  virtual int32_t SetInputTensor(int32_t input_index,
                                 std::shared_ptr<DNNTensor> &input_tensor) = 0;

  /**
   * Set all input tensors
   * @param[in] input_tensors
   * @return 0 if success, return defined error code otherwise
   */
  virtual int32_t SetInputTensors(
      std::vector<std::shared_ptr<DNNTensor>> &input_tensors) = 0;

  /**
   * Set one output tensor
   * @param[in] output_index
   * @param[in] output_tensor
   * @return 0 if success, return defined error code otherwise
   */
  virtual int32_t SetOutputTensor(
      int32_t output_index, std::shared_ptr<DNNTensor> &output_tensor) = 0;

  /**
   * Set all output tensors
   * @param[in] output_tensors
   * @return 0 if success, return defined error code otherwise
   */
  virtual int32_t SetOutputTensors(
      std::vector<std::shared_ptr<DNNTensor>> &output_tensors) = 0;

  /**
   * Get one output tensor
   * @param[out] output_tensor
   * @param[in] output_index
   * @return 0 if success, return defined error code otherwise
   */
  virtual int32_t GetOutputTensor(std::shared_ptr<DNNTensor> &output_tensor,
                                  int32_t output_index) = 0;

  /**
   * Get all output tensors
   * @param[out] output_tensors
   * @return 0 if success, return defined error code otherwise
   */
  virtual int32_t GetOutputTensors(
      std::vector<std::shared_ptr<DNNTensor>> &output_tensors) = 0;

  /**
   * Set one output result holder
   * @param[in] output_index
   * @param[in] output
   * @return 0 if success, return defined error code otherwise
   */
  virtual int32_t SetOutput(int32_t output_index,
                            std::shared_ptr<DNNResult> output) = 0;

  /**
   * Set all output result holder
   * @param[in] output
   * @return 0 if success, return defined error code otherwise
   */
  virtual int32_t SetOutputs(
      std::vector<std::shared_ptr<DNNResult>> &outputs) = 0;

  /**
   * Get one output result
   * @param[in] output_index
   * @param[out] output
   * @return 0 if success, return defined error code otherwise
   */
  virtual int32_t GetOutput(std::shared_ptr<DNNResult> &output,
                            int32_t output_index) = 0;

  /**
   * Get all output result
   * @param[out] outputs
   * @return 0 if success, return defined error code otherwise
   */
  virtual int32_t GetOutputs(
      std::vector<std::shared_ptr<DNNResult>> &outputs) = 0;
};

class ModelRoiInferTask : virtual public ModelTask {
 public:
  /**
   * Set roi number (non-required)
   * @param[in] roi_num
   * @return 0 if success, return defined error code otherwise
   */
  virtual int32_t SetInputRoiNum(int32_t roi_num) = 0;

  /**
   * Set roi (non-required)
   * @param[in] roi_index
   * @param[in] roi
   * @return 0 if success, return defined error code otherwise
   */
  virtual int32_t SetInputRoi(int32_t roi_index, hbDNNRoi &roi) = 0;

  /**
   * Set input rois (non-required)
   * @param[in] rois
   * @return 0 if success, return defined error code otherwise
   */
  virtual int32_t SetInputRois(std::vector<hbDNNRoi> &rois) = 0;

  /**
   * Set one input for specified roi (non-required)
   * @param[in] roi_index
   * @param[in] input_index
   * @param[in] input
   * @return 0 if success, return defined error code otherwise
   */
  virtual int32_t SetInput(int32_t roi_index,
                           int32_t input_index,
                           std::shared_ptr<DNNInput> &input) = 0;

  /**
   * Set inputs for specified roi (non-required)
   * @param[in] roi_index
   * @param[in] inputs
   * @return 0 if success, return defined error code otherwise
   */
  virtual int32_t SetInputs(int32_t roi_index,
                            std::vector<std::shared_ptr<DNNInput>> &inputs) = 0;

  /**
   * Set inputs for all roi (non-required)
   * @param[in] inputs
   * @return 0 if success, return defined error code otherwise
   */
  virtual int32_t SetInputs(std::vector<std::shared_ptr<DNNInput>> &inputs) = 0;

  /**
   * Set one input tensor for specified roi (non-required)
   * @param[in] roi_index
   * @param[in] input_index
   * @param[in] input_tensor
   * @return 0 if success, return defined error code otherwise
   */
  virtual int32_t SetInputTensor(int32_t roi_index,
                                 int32_t input_index,
                                 std::shared_ptr<DNNTensor> &input_tensor) = 0;

  /**
   * Set input tensors for specified roi (non-required)
   * @param[in] roi_index
   * @param[in] input_tensors
   * @return 0 if success, return defined error code otherwise
   */
  virtual int32_t SetInputTensors(
      int32_t roi_index,
      std::vector<std::shared_ptr<DNNTensor>> &input_tensors) = 0;

  /**
   * Set input tensors for all roi (non-required)
   * @param[in] input_tensors
   * @return 0 if success, return defined error code otherwise
   */
  virtual int32_t SetInputTensors(
      std::vector<std::shared_ptr<DNNTensor>> &input_tensors) = 0;

  /**
   * Set output tensor for specified output (non-required)
   * @param[in] output_index
   * @param[in] output_tensor (batch tensor of one input branch for all rois  )
   * @return 0 if success, return defined error code otherwise
   */
  virtual int32_t SetOutputTensor(
      int32_t output_index, std::shared_ptr<DNNTensor> &output_tensor) = 0;

  /**
   * Set output tensors for all roi (non-required)
   * @param[in] output_tensors the size should be equal to output count
   * @return 0 if success, return defined error code otherwise
   */
  virtual int32_t SetOutputTensors(
      std::vector<std::shared_ptr<DNNTensor>> &output_tensors) = 0;

  /**
   * Get one output tensor for specified roi
   * @param roi_index
   * @param output_index
   * @param output_tensor
   * @return 0 if success, return defined error code otherwise
   */
  virtual int32_t GetOutputTensor(std::shared_ptr<DNNTensor> &output_tensor,
                                  int32_t roi_index,
                                  int32_t output_index) = 0;

  /**
   * Get all outputs of specified roi (non-required)
   * @param[in] roi_index
   * @param[out] output_tensors, the size equal to model output count
   * @return 0 if success, return defined error code otherwise
   */
  virtual int32_t GetOutputTensors(
      std::vector<std::shared_ptr<DNNTensor>> &output_tensors,
      int32_t roi_index) = 0;

  /**
   * Get all output tensors, batch layout
   * @param[out] output_tensors, the size equal to model output count
   * @return 0 if success, return defined error code otherwise
   */
  virtual int32_t GetOutputTensors(
      std::vector<std::shared_ptr<DNNTensor>> &output_tensors) = 0;

  /**
   * Get all output tensors,
   * @param[out] output_tensors, the size equal to roi count and
   *    each element's size is model output count
   * @return 0 if success, return defined error code otherwise
   */
  virtual int32_t GetOutputTensors(
      std::vector<std::vector<std::shared_ptr<DNNTensor>>> &output_tensors) = 0;

  /**
   * Set one output result holder for specified roi
   * @param[in] roi_index
   * @param[in] output_index
   * @param[in] output
   * @return 0 if success, return defined error code otherwise
   */
  virtual int32_t SetOutput(int32_t roi_index,
                            int32_t output_index,
                            std::shared_ptr<DNNResult> output) = 0;

  /**
   * Set output result holder for specified roi
   * @param[in] roi_index
   * @param[in] outputs
   * @return 0 if success, return defined error code otherwise
   */
  virtual int32_t SetOutputs(
      int32_t roi_index, std::vector<std::shared_ptr<DNNResult>> &outputs) = 0;

  /**
   * Set output result holder for all rois
   * @param[in] outputs
   * @return 0 if success, return defined error code otherwise
   */
  virtual int32_t SetOutputs(
      std::vector<std::shared_ptr<DNNResult>> &outputs) = 0;

  /**
   * Get one infer result for specified roi
   * @param[in] roi_index
   * @param[in] output_index
   * @param[out] output
   * @return 0 if success, return defined error code otherwise
   */
  virtual int32_t GetOutput(std::shared_ptr<DNNResult> &output,
                            int32_t roi_index,
                            int32_t output_index) = 0;

  /**
   * Get all infer result for specified roi
   * @param[out] outputs
   * @param[in] roi_index
   * @return 0 if success, return defined error code otherwise
   */
  virtual int32_t GetOutputs(std::vector<std::shared_ptr<DNNResult>> &outputs,
                             int32_t roi_index) = 0;

  /**
   * Get all infer result for all rois
   * @param[out] outputs
   * @return 0 if success, return defined error code otherwise
   */
  virtual int32_t GetOutputs(
      std::vector<std::shared_ptr<DNNResult>> &outputs) = 0;
};

class MultiModelTask : public Task {
 public:
  /**
   * Add subtask
   * @param[in] task
   * @return 0 if success, return defined error code otherwise
   */
  virtual int32_t AddTask(std::shared_ptr<ModelTask> task) = 0;

  /**
   * Get all subtasks
   * @return all subtasks
   */
  virtual std::vector<std::shared_ptr<ModelTask>> &GetTasks() = 0;
};

}  // namespace easy_dnn
}  // namespace hobot

#endif  // _EASY_DNN_TASK_H_
