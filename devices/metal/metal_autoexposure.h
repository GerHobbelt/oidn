// Copyright 2023 Apple Inc.
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "core/autoexposure.h"
#include "metal_engine.h"

OIDN_NAMESPACE_BEGIN

  class MetalAutoexposure final : public Autoexposure
  {
  public:
    MetalAutoexposure(const Ref<MetalEngine>& engine, const ImageDesc& srcDesc);
    ~MetalAutoexposure();

    void finalize() override;
    void submit() override;

    const float* getResult() const override { return &result; }
    
  private:
    void cleanup();
    void downsample();
    void reduce();
    AutoexposureParams createProcessParams();
    
  private:
    Ref<MetalEngine> engine;
    float result;
    
    MTLComputePipelineState_t pipelineDownsample;
    MTLComputePipelineState_t pipelineReduce;
    MTLCommandQueue_t commandQueue;
    MTLBuffer_t paramsBuffer;
    
    std::shared_ptr<Tensor> binsTensor;
    std::shared_ptr<Tensor> sumsTensor;
    std::shared_ptr<Tensor> countsTensor;
    std::shared_ptr<Tensor> outputTensor;
  };

OIDN_NAMESPACE_END
