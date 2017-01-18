//===-- ToyVLIWTargetMachine.cpp - Define TargetMachine for ToyVLIW -----------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
//
//===----------------------------------------------------------------------===//

#include "ToyVLIWTargetMachine.h"
#include "ToyVLIW.h"
#include "ToyVLIWFrameLowering.h"
#include "ToyVLIWInstrInfo.h"
#include "ToyVLIWISelLowering.h"
#include "ToyVLIWSelectionDAGInfo.h"
#include "llvm/CodeGen/Passes.h"
#include "llvm/CodeGen/TargetLoweringObjectFileImpl.h"
#include "llvm/CodeGen/TargetPassConfig.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/PassManager.h"
#include "llvm/Support/TargetRegistry.h"

using namespace llvm;

static std::string computeDataLayout(const Triple &TT, StringRef CPU,
                                     const TargetOptions &Options) {
  // XXX Build the triple from the arguments.
  return "e-m:e-p:32:32-i1:8:32-i8:8:32-i16:16:32-i64:32-f64:32-a:0:32-n32";
}

static Reloc::Model getEffectiveRelocModel(const Triple &TT,
                                           Optional<Reloc::Model> RM) {
  // On ELF platforms the default static relocation model has a smart enough
  // linker to cope with referencing external symbols defined in a shared
  // library. Hence DynamicNoPIC doesn't need to be promoted to PIC.
  if (!RM.hasValue() || *RM == Reloc::DynamicNoPIC)
    return Reloc::Static;
  return *RM;
}


ToyVLIWTargetMachine::ToyVLIWTargetMachine(
    const Target &T, const Triple &TT, StringRef CPU, StringRef FS,
    const TargetOptions &Options, Optional<Reloc::Model> RM,
    CodeModel::Model CM, CodeGenOpt::Level OL)
    : LLVMTargetMachine(T, computeDataLayout(TT, CPU, Options), TT, CPU, FS,
                        Options, getEffectiveRelocModel(TT, RM), CM, OL),
      Subtarget(TT, CPU, FS, *this),
      TLOF(make_unique<TargetLoweringObjectFileELF>()) {

  initAsmInfo();
}

namespace {
/// ToyVLIW Code Generator Pass Configuration Options.
class ToyVLIWPassConfig : public TargetPassConfig {
public:
  ToyVLIWPassConfig(ToyVLIWTargetMachine *TM, PassManagerBase &PM)
      : TargetPassConfig(TM, PM) {}

  ToyVLIWTargetMachine &getToyVLIWTargetMachine() const {
    return getTM<ToyVLIWTargetMachine>();
  }

  virtual bool addPreISel() override;
  virtual bool addInstSelector() override;
};
} // namespace

TargetPassConfig *ToyVLIWTargetMachine::createPassConfig(PassManagerBase &PM) {
  return new ToyVLIWPassConfig(this, PM);
}

bool ToyVLIWPassConfig::addPreISel() { return false; }

bool ToyVLIWPassConfig::addInstSelector() {
  addPass(createToyVLIWISelDag(getToyVLIWTargetMachine(), getOptLevel()));
  return false;
}

// Force static initialization.
extern "C" void LLVMInitializeToyVLIWTarget() {
  RegisterTargetMachine<ToyVLIWTargetMachine> X(getTheToyVLIWTarget());
}
