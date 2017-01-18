//===-- ToyVLIWSelectionDAGInfo.h - ToyVLIW SelectionDAG Info -------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file defines the ToyVLIW subclass for TargetSelectionDAGInfo.
//
//===----------------------------------------------------------------------===//

#pragma once

#include "llvm/CodeGen/SelectionDAGTargetInfo.h"

namespace llvm {

class ToyVLIWSelectionDAGInfo : public SelectionDAGTargetInfo {
public:
  ~ToyVLIWSelectionDAGInfo();
};
}
