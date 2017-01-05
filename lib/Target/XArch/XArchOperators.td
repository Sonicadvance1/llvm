//===-- XArchOperators.td - XArch-specific operators ------*- tblgen-*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

def MoveImm32Ty : SDTypeProfile<1, 1, [
  SDTCisSameAs<0, 1>, SDTCisInt<0>
]>;
def i16_imm : Operand<i32>, ImmLeaf<i32, [{ return (Imm & ~0xFFFF) == 0; }]>;


def XArchcallseq_start : SDNode<"ISD::CALLSEQ_START",
                                SDCallSeqStart<[ SDTCisVT<0, i32> ]>,
                                [SDNPHasChain, SDNPOutGlue]>;
def XArchcallseq_end   : SDNode<"ISD::CALLSEQ_END",
                                SDCallSeqEnd<[ SDTCisVT<0, i32>,
                                               SDTCisVT<1, i32> ]>,
                                [SDNPHasChain, SDNPOptInGlue, SDNPOutGlue]>;

def XArchRetFlag    : SDNode<"XArchISD::RET_FLAG", SDTNone,
                           [SDNPHasChain, SDNPOptInGlue, SDNPVariadic]>;

def movei32 : SDNode<"XArchISD::MOVEi32", MoveImm32Ty>;
