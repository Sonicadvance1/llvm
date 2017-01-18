//===-- ToyVLIWInstrInfo.cpp - ToyVLIW Instruction Information ----------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains the ToyVLIW implementation of the TargetInstrInfo class.
//
//===----------------------------------------------------------------------===//

#include "ToyVLIWInstrInfo.h"
#include "ToyVLIW.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/CodeGen/MachineConstantPool.h"
#include "llvm/CodeGen/MachineFrameInfo.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/CodeGen/MachineMemOperand.h"
#include "llvm/CodeGen/ScheduleDAG.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/Function.h"
#include "llvm/MC/MCContext.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/TargetRegistry.h"

#define GET_INSTRINFO_CTOR_DTOR
#include "ToyVLIWGenInstrInfo.inc"

using namespace llvm;

// Pin the vtable to this file.
void ToyVLIWInstrInfo::anchor() {}

ToyVLIWInstrInfo::ToyVLIWInstrInfo()
  : ToyVLIWGenInstrInfo(),
    RI() {
}

//===----------------------------------------------------------------------===//
// Branch Analysis
//===----------------------------------------------------------------------===//
//
/// AnalyzeBranch - Analyze the branching code at the end of MBB, returning
/// true if it cannot be understood (e.g. it's a switch dispatch or isn't
/// implemented for a target).  Upon success, this returns false and returns
/// with the following information in various cases:
///
/// 1. If this block ends with no branches (it just falls through to its succ)
///    just return false, leaving TBB/FBB null.
/// 2. If this block ends with only an unconditional branch, it sets TBB to be
///    the destination block.
/// 3. If this block ends with an conditional branch and it falls through to
///    an successor block, it sets TBB to be the branch destination block and a
///    list of operands that evaluate the condition. These
///    operands can be passed to other TargetInstrInfo methods to create new
///    branches.
/// 4. If this block ends with an conditional branch and an unconditional
///    block, it returns the 'true' destination in TBB, the 'false' destination
///    in FBB, and a list of operands that evaluate the condition. These
///    operands can be passed to other TargetInstrInfo methods to create new
///    branches.
///
/// Note that RemoveBranch and InsertBranch must be implemented to support
/// cases where this method returns success.
///
bool ToyVLIWInstrInfo::analyzeBranch(MachineBasicBlock &MBB, MachineBasicBlock *&TBB,
                   MachineBasicBlock *&FBB,
                   SmallVectorImpl<MachineOperand> &Cond,
                   bool AllowModify) const {
  // XXX: Needs to be properly implemented when implementing branching support otherwise phi nodes explode!
  return false;
}

/// RemoveBranch - Remove the branching code at the end of the specific MBB.
/// This is only invoked in cases where AnalyzeBranch returns success. It
/// returns the number of instructions that were removed.
unsigned ToyVLIWInstrInfo::removeBranch(MachineBasicBlock &MBB,
                      int *BytesRemoved) const {
  // XXX:
  llvm_unreachable("unimplemented");
  return 0;
}

/// InsertBranch - Insert branch code into the end of the specified
/// MachineBasicBlock.  The operands to this method are the same as those
/// returned by AnalyzeBranch.  This is only invoked in cases where
/// AnalyzeBranch returns success. It returns the number of instructions
/// inserted.
///
/// It is also invoked by tail merging to add unconditional branches in
/// cases where AnalyzeBranch doesn't apply because there was no original
/// branch to analyze.  At least this much must be implemented, else tail
/// merging needs to be disabled.
unsigned ToyVLIWInstrInfo::insertBranch(MachineBasicBlock &MBB, MachineBasicBlock *TBB,
                    MachineBasicBlock *FBB, ArrayRef<MachineOperand> Cond,
                      const DebugLoc &DL,
                      int *BytesAdded) const {
  // XXX:
  llvm_unreachable("unimplemented");
  return 0;
}

void ToyVLIWInstrInfo::copyPhysReg(MachineBasicBlock &MBB, MachineBasicBlock::iterator I,
                 const DebugLoc &DL, unsigned DestReg, unsigned SrcReg,
                 bool KillSrc) const {
  // XXX:
  llvm_unreachable("unimplemented");
}

void ToyVLIWInstrInfo::storeRegToStackSlot(MachineBasicBlock &MBB,
                                         MachineBasicBlock::iterator I,
                                         unsigned SrcReg, bool isKill,
                                         int FrameIndex,
                                         const TargetRegisterClass *RC,
                                         const TargetRegisterInfo *TRI) const
{
  // XXX:
  llvm_unreachable("unimplemented");
}

void ToyVLIWInstrInfo::loadRegFromStackSlot(MachineBasicBlock &MBB,
                                          MachineBasicBlock::iterator I,
                                          unsigned DestReg, int FrameIndex,
                                          const TargetRegisterClass *RC,
                                          const TargetRegisterInfo *TRI) const
{
  // XXX:
  llvm_unreachable("unimplemented");
}

bool ToyVLIWInstrInfo::expandPostRAPseudo(MachineInstr &MI) const {
  switch (MI.getOpcode())
  {
  default:
    return false;
  }
}

void ToyVLIWInstrInfo::insertNoop(MachineBasicBlock &MBB,
                                MachineBasicBlock::iterator MI) const {
  // XXX:
  llvm_unreachable("unimplemented");
}

