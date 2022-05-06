// Copyright 2009-2022 Intel Corporation
// SPDX-License-Identifier: Apache-2.0

#include "cutlass_conv.h"

namespace oidn {

// Volta
template<>
std::vector<CutlassConvFactory> getCutlassConvInstances<70>()
{
  using namespace cutlass::arch;
  using cutlass::gemm::GemmShape;

  return {
    CutlassConvInstance<half, Sm70, GemmShape<256, 32, 32>, GemmShape<64, 32, 32>, 2>::get(),
    CutlassConvInstance<half, Sm70, GemmShape<256, 64, 32>, GemmShape<64, 64, 32>, 2>::get(),
  };
}

} // namespace oidn