//=- ToyVLIWRegisterInfo.td - Describe the ToyVLIW Registers -*- tablegen -*-=//
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

class ToyVLIWReg<bits<16> enc, string n>
        : Register<n> {
  let HWEncoding = enc;
  let Namespace = "ToyVLIW";
}

// CPU registers
foreach Index = 0-64 in {
  def R#Index : ToyVLIWReg <Index, "R"#Index>;
}

def INVALID : ToyVLIWReg <255, "INVALID">;

// Register classes.
//
def GPRegs : RegisterClass<"ToyVLIW", [i64, i32, i16, i8, i1], 64,
  // Return values and arguments
  (add (sequence "R%u", 0, 64))>;
