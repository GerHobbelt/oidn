// Copyright 2009-2022 Intel Corporation
// SPDX-License-Identifier: Apache-2.0

#include "cpu_output_process.h"
#include "cpu_output_process_ispc.h"

namespace oidn {

  CPUOutputProcess::CPUOutputProcess(const Ref<CPUDevice>& device, const OutputProcessDesc& desc)
    : OutputProcess(desc),
      device(device) {}

  void CPUOutputProcess::run()
  {
    assert(tile.hSrcBegin + tile.H <= src->getH());
    assert(tile.wSrcBegin + tile.W <= src->getW());
    //assert(tile.hDstBegin + tile.H <= output->getH());
    //assert(tile.wDstBegin + tile.W <= output->getW());

    ispc::CPUOutputProcessKernel kernel;

    kernel.src = *src;
    kernel.dst = *dst;
    kernel.tile = tile;
    kernel.transferFunc = *transferFunc;
    kernel.hdr = hdr;
    kernel.snorm = snorm;

    parallel_nd(kernel.tile.H, [&](int h)
    {
      ispc::CPUOutputProcessKernel_run(&kernel, h);
    });
  }

} // namespace oidn