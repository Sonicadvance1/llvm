//===- ToyVLIWCallingConv.td - Calling Conventions for ToyVLIW -*- tablegen -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
// This describes the calling conventions for ToyVLIW architecture.
//===----------------------------------------------------------------------===//

//===----------------------------------------------------------------------===//
// ToyVLIW Return Value Calling Convention
//===----------------------------------------------------------------------===//
def RetCC_ToyVLIW : CallingConv<[
  CCIfType<[i64, i32, i16, i8, i1], CCAssignToReg<[R0, R1, R2, R3, R4, R5, R6, R7, R8, R9, R10, R11, R12, R13]>>,

  // Integer values get stored in stack slots that are 4 bytes in
  // size and 4-byte aligned.
  CCIfType<[f32], CCAssignToStack<4, 4>>
]>;

//===----------------------------------------------------------------------===//
// ToyVLIW Argument Calling Conventions
//===----------------------------------------------------------------------===//
def CC_ToyVLIW : CallingConv<[
  CCIfType<[i64, i32, i16, i8, i1], CCAssignToReg<[R0, R1, R2, R3, R4, R5, R6, R7, R8, R9, R10, R11, R12, R13]>>,

  // Integer values get stored in stack slots that are 4 bytes in
  // size and 4-byte aligned.
  CCIfType<[f32], CCAssignToStack<4, 4>>
]>;
