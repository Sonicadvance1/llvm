//===-- ToyVLIW.h - Top-level interface for ToyVLIW representation --*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains the entry points for global functions defined in the LLVM
// ToyVLIW back-end.
//
//===----------------------------------------------------------------------===//

#pragma once

#include "MCTargetDesc/ToyVLIWMCTargetDesc.h"
#include "llvm/Target/TargetMachine.h"

namespace llvm {
class TargetMachine;
class ToyVLIWTargetMachine;

FunctionPass *createToyVLIWISelDag(ToyVLIWTargetMachine &TM,
                               CodeGenOpt::Level OptLevel);
} // end namespace llvm;
