//===-- ToyVLIWTargetInfo.cpp - ToyVLIW Target Implementation -----------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "llvm/ADT/Triple.h"
#include "llvm/Support/TargetRegistry.h"
using namespace llvm;
namespace llvm {
Target &getTheToyVLIWTarget() {
  static Target TheToyVLIWTarget;
  return TheToyVLIWTarget;
}
} // namespace llvm

extern "C" void LLVMInitializeToyVLIWTargetInfo() {
  RegisterTarget<Triple::toyvliw, true> X(getTheToyVLIWTarget(), "ToyVLIW",
                                          "ToyVLIW");
}
