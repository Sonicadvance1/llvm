//===-- ToyVLIWMCTargetDesc.cpp - ToyVLIW Target Descriptions -----------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file provides ToyVLIW specific target descriptions.
//
//===----------------------------------------------------------------------===//

#include "ToyVLIWMCTargetDesc.h"
#include "InstPrinter/ToyVLIWInstPrinter.h"
#include "ToyVLIWMCAsmInfo.h"
#include "llvm/MC/MCInstrInfo.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/MC/MCStreamer.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/FormattedStream.h"
#include "llvm/Support/TargetRegistry.h"

#define GET_INSTRINFO_MC_DESC
#include "ToyVLIWGenInstrInfo.inc"

#define GET_SUBTARGETINFO_MC_DESC
#include "ToyVLIWGenSubtargetInfo.inc"

#define GET_REGINFO_MC_DESC
#include "ToyVLIWGenRegisterInfo.inc"

using namespace llvm;

static MCInstrInfo *createToyVLIWMCInstrInfo() {
  MCInstrInfo *X = new MCInstrInfo();
  InitToyVLIWMCInstrInfo(X);
  return X;
}

static MCRegisterInfo *createToyVLIWMCRegisterInfo(const Triple &TT) {
  MCRegisterInfo *X = new MCRegisterInfo();
  InitToyVLIWMCRegisterInfo(X, ToyVLIW::INVALID);
  return X;
}

static MCSubtargetInfo *createToyVLIWMCSubtargetInfo(const Triple &TT,
                                                 StringRef CPU,
                                                 StringRef FS) {
  return createToyVLIWMCSubtargetInfoImpl(TT, CPU, FS);
}

static MCAsmInfo *createToyVLIWMCAsmInfo(const MCRegisterInfo &MRI,
                                     const Triple &TT) {
  return new ToyVLIWMCAsmInfo(TT);
}

static void adjustCodeGenOpts(const Triple &TT, Reloc::Model RM,
                              CodeModel::Model &CM) {
  assert(TT.isOSBinFormatELF() &&
         "Only expect ELF targets");

  if (CM == CodeModel::Default)
    CM = CodeModel::Small;
  else if (CM != CodeModel::Small)
    report_fatal_error(
        "Only small code model allowed");
}

static MCInstPrinter *
createToyVLIWMCInstPrinter(const Triple &TT, unsigned SyntaxVariant,
                       const MCAsmInfo &MAI, const MCInstrInfo &MII,
                       const MCRegisterInfo &MRI) {
  return new ToyVLIWInstPrinter(MAI, MII, MRI);
}

// Force static initialization.
extern "C" void LLVMInitializeToyVLIWTargetMC() {
  // Register the MC asm info.
  RegisterMCAsmInfoFn X(getTheToyVLIWTarget(), createToyVLIWMCAsmInfo);

  // Register the MC codegen info.
  TargetRegistry::registerMCAdjustCodeGenOpts(getTheToyVLIWTarget(), adjustCodeGenOpts);

  // Register the MC instruction info.
  TargetRegistry::RegisterMCInstrInfo(getTheToyVLIWTarget(), createToyVLIWMCInstrInfo);

  // Register the MC register info.
  TargetRegistry::RegisterMCRegInfo(getTheToyVLIWTarget(), createToyVLIWMCRegisterInfo);

  // Register the MC subtarget info.
  TargetRegistry::RegisterMCSubtargetInfo(getTheToyVLIWTarget(),
                                          createToyVLIWMCSubtargetInfo);

  // Register the MCInstPrinter
  TargetRegistry::RegisterMCInstPrinter(getTheToyVLIWTarget(), createToyVLIWMCInstPrinter);

  // Register the ASM Backend.
  TargetRegistry::RegisterMCAsmBackend(getTheToyVLIWTarget(), createToyVLIWAsmBackend);

  // Register the MCCodeEmitter
  TargetRegistry::RegisterMCCodeEmitter(getTheToyVLIWTarget(), createToyVLIWMCCodeEmitter);
}
