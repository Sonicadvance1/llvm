//=- ToyVLIW.td - Describe the ToyVLIW Target Machine --------*- tablegen -*-=//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
// Target-independent interfaces which we are implementing.
//===----------------------------------------------------------------------===//

include "llvm/Target/Target.td"

//===----------------------------------------------------------------------===//
// Descriptions
//===----------------------------------------------------------------------===//

include "ToyVLIWRegisterInfo.td"
include "ToyVLIWInstrInfo.td"
include "ToyVLIWCallingConv.td"

def ToyVLIWInstrInfo : InstrInfo;

//===----------------------------------------------------------------------===//
// ToyVLIW processors supported.
//===----------------------------------------------------------------------===//

class Proc<string Name, list<SubtargetFeature> Features>
    : Processor<Name, NoItineraries, Features>;

def : Proc<"generic", []>;


//===----------------------------------------------------------------------===//
// The target
//===----------------------------------------------------------------------===//

def ToyVLIW : Target {
  let InstructionSet = ToyVLIWInstrInfo;
}
