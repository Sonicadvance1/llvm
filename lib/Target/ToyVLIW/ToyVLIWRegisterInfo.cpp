//===-- ToyVLIWRegisterInfo.cpp - ToyVLIW Register Information ----------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains the ToyVLIW implementation of the MRegisterInfo class.
//
//===----------------------------------------------------------------------===//

#include "ToyVLIWRegisterInfo.h"
#include "ToyVLIW.h"
#include "ToyVLIWFrameLowering.h"
#include "ToyVLIWInstrInfo.h"
#include "ToyVLIWMachineFunctionInfo.h"
#include "llvm/ADT/BitVector.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/CodeGen/MachineFrameInfo.h"
#include "llvm/CodeGen/MachineFunction.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/CodeGen/MachineModuleInfo.h"
#include "llvm/CodeGen/MachineRegisterInfo.h"
#include "llvm/CodeGen/RegisterScavenging.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Type.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/MathExtras.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Target/TargetFrameLowering.h"
#include "llvm/Target/TargetMachine.h"
#include "llvm/Target/TargetOptions.h"

#define GET_REGINFO_TARGET_DESC
#include "ToyVLIWGenRegisterInfo.inc"

using namespace llvm;

ToyVLIWRegisterInfo::ToyVLIWRegisterInfo() : ToyVLIWGenRegisterInfo(ToyVLIW::INVALID) {}

const uint16_t *
ToyVLIWRegisterInfo::getCalleeSavedRegs(const MachineFunction *MF) const {
  static const uint16_t CalleeSavedRegs[] = { ToyVLIW::R4, ToyVLIW::R5, ToyVLIW::R6,
                                              ToyVLIW::R7, ToyVLIW::R8, ToyVLIW::R9,
                                              0 };
  return CalleeSavedRegs;
}

BitVector ToyVLIWRegisterInfo::getReservedRegs(const MachineFunction &MF) const {
  BitVector Reserved(getNumRegs());

  return Reserved;
}

const uint32_t *ToyVLIWRegisterInfo::getCallPreservedMask(const MachineFunction &MF,
                                                      CallingConv::ID) const {
  return 0;
}

bool
ToyVLIWRegisterInfo::requiresRegisterScavenging(const MachineFunction &MF) const {
  return true;
}

bool
ToyVLIWRegisterInfo::trackLivenessAfterRegAlloc(const MachineFunction &MF) const {
  return true;
}

bool ToyVLIWRegisterInfo::useFPForScavengingIndex(const MachineFunction &MF) const {
  return false;
}

void ToyVLIWRegisterInfo::eliminateFrameIndex(MachineBasicBlock::iterator II,
                                          int SPAdj, unsigned FIOperandNum,
                                          RegScavenger *RS) const {
  // Not supported yet.
  llvm_unreachable("Couldn't reach here");
}

unsigned ToyVLIWRegisterInfo::getFrameRegister(const MachineFunction &MF) const {
  return ToyVLIW::INVALID;
}
