//===-- XArchInstrInfo.td - Target Description for XArch ---*- tablegen -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file describes the XArch instructions in TableGen format.
//
//===----------------------------------------------------------------------===//

include "XArchInstrFormats.td"
include "XArchOperators.td"

//===----------------------------------------------------------------------===//
// ALU Instructions
//===----------------------------------------------------------------------===//
multiclass BinOp<bits<4> opcode, string opstr, SDNode opnode> {
  def rr : ALUInst<opcode, (outs GRRegs:$dst),
                   (ins GRRegs:$src1, GRRegs:$src2),
                   !strconcat(opstr, " $dst, $src1, $src2"),
                   [(set i32:$dst, (opnode i32:$src1, i32:$src2))]> {
  }
}

defm ADD  : BinOp<0b0000, "add", add>;

//===----------------------------------------------------------------------===//
// Mov Instructions
//===----------------------------------------------------------------------===//
def MOVrr  : ALUInst<0b1101, (outs GRRegs:$dst), (ins GRRegs:$src),
                     "mov $dst, $src",
                     [/* No pattern */]> {
}

def MOVi32 : InstXArch<(outs GRRegs:$dst), (ins i32imm:$src), "mov $dst, $src",
                     [(set i32:$dst, i16_imm:$src)]> {
  bits<7> dst;
  bits<16> src;

  let Inst{31-30} = 0b00;
  let Inst{29-26} = 0b1110;
  let Inst{25-19} = dst;
  let Inst{15-0} = src;

}

//===----------------------------------------------------------------------===//
// Pseudo Instructions
//===----------------------------------------------------------------------===//

let Defs = [SP], Uses = [SP] in {
def ADJCALLSTACKDOWN : XArchPseudoInst<(outs), (ins i32imm:$amt),
                                    "# ADJCALLSTACKDOWN $amt",
                                    [(XArchcallseq_start timm:$amt)]>;
def ADJCALLSTACKUP   : XArchPseudoInst<(outs), (ins i32imm:$amt1, i32imm:$amt2),
                                    "# ADJCALLSTACKUP $amt1",
                                    [(XArchcallseq_end timm:$amt1, timm:$amt2)]>;
}

//===----------------------------------------------------------------------===//
// Return Instructions
//===----------------------------------------------------------------------===//

let isTerminator = 1, isReturn = 1, isBarrier = 1, Uses = [LR] in {
  def RET : InstXArch<(outs), (ins variable_ops),
                    "ret",  [(XArchRetFlag)]> {
    let Inst{29-26} = 0b1111;

  }
}
