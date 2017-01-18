//===-- ToyVLIWTargetMachine.h - Define TargetMachine for ToyVLIW ---*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file declares the ToyVLIW specific subclass of TargetMachine.
//
//===----------------------------------------------------------------------===//

#pragma once

#include "ToyVLIW.h"
#include "ToyVLIWFrameLowering.h"
#include "ToyVLIWISelLowering.h"
#include "ToyVLIWInstrInfo.h"
#include "ToyVLIWSelectionDAGInfo.h"
#include "ToyVLIWSubtarget.h"
#include "llvm/IR/DataLayout.h"
#include "llvm/Target/TargetMachine.h"

namespace llvm {

class ToyVLIWTargetMachine : public LLVMTargetMachine {
  ToyVLIWSubtarget Subtarget;
  std::unique_ptr<TargetLoweringObjectFile> TLOF;

public:
  ToyVLIWTargetMachine(const Target &T, const Triple &TT, StringRef CPU, StringRef FS,
                     const TargetOptions &Options, Optional<Reloc::Model> RM,
                     CodeModel::Model CM, CodeGenOpt::Level OL);

  const ToyVLIWSubtarget * getSubtargetImpl() const {
    return &Subtarget;
  }

  virtual const TargetSubtargetInfo *
  getSubtargetImpl(const Function &) const override {
    return &Subtarget;
  }

  // Pass Pipeline Configuration
  virtual TargetPassConfig *createPassConfig(PassManagerBase &PM) override;

  TargetLoweringObjectFile *getObjFileLowering() const override {
    return TLOF.get();
  }
};

} // end namespace llvm
