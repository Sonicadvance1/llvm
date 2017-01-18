//=- ToyVLIWInstrInfo.td - Describe the ToyVLIW Target Machine -*- tablegen -*-=//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
//===----------------------------------------------------------------------===//

include "ToyVLIWInstrFormats.td"
include "ToyVLIWOperators.td"

//===----------------------------------------------------------------------===//
//
//===----------------------------------------------------------------------===//

def NOP : InstToyVLIW<(outs), (ins), "nop", [/* No Pattern */]> {
  let Inst{0} = 1;
}

let isTerminator = 1, isReturn = 1, isBarrier = 1 in {
  def RET
    : InstToyVLIW<(outs), (ins variable_ops),
                   "ret",  [(ToyVLIWRetFlag)]>
  {
    let Inst{1-0} = 0b10;
  }
}
