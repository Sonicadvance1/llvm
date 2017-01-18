//===-- ToyVLIWMachineFuctionInfo.h - ToyVLIW machine function info -*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file declares ToyVLIW-specific per-machine-function information.
//
//===----------------------------------------------------------------------===//

#pragma once

#include "llvm/CodeGen/MachineFrameInfo.h"
#include "llvm/CodeGen/MachineFunction.h"

namespace llvm {

// Forward declarations
class Function;

/// ToyVLIWFunctionInfo - This class is derived from MachineFunction private
/// ToyVLIW target-specific information for each MachineFunction.
class ToyVLIWFunctionInfo : public MachineFunctionInfo {
public:
  ToyVLIWFunctionInfo() {}

  ~ToyVLIWFunctionInfo() {}
};
} // End llvm namespace
