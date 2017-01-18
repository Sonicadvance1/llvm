//===- ToyVLIWDisassembler.cpp - Disassembler for ToyVLIW -------*- C++ -*-===//
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

#include "ToyVLIWDisassembler.h"
#include "ToyVLIWSubtarget.h"
#include "MCTargetDesc/ToyVLIWMCTargetDesc.h"
#include "llvm/MC/MCFixedLenDisassembler.h"
#include "llvm/MC/MCInst.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/TargetRegistry.h"

using namespace llvm;

#define DEBUG_TYPE "toyvliw-disassembler"

// Pull DecodeStatus and its enum values into the global namespace.
typedef llvm::MCDisassembler::DecodeStatus DecodeStatus;

#include "ToyVLIWGenDisassemblerTables.inc"
#include "ToyVLIWGenInstrInfo.inc"

#define Success llvm::MCDisassembler::Success
#define Fail llvm::MCDisassembler::Fail
#define SoftFail llvm::MCDisassembler::SoftFail

static MCDisassembler *createToyVLIWDisassembler(const Target &T,
                                               const MCSubtargetInfo &STI,
                                               MCContext &Ctx) {
  return new ToyVLIWDisassembler(STI, Ctx);
}

template <typename T> static inline T eatBytes(ArrayRef<uint8_t>& Bytes) {
  assert(Bytes.size() >= sizeof(T));
  const auto Res = support::endian::read<T, support::endianness::little>(Bytes.data());
  Bytes = Bytes.slice(sizeof(T));
  return Res;
}

DecodeStatus ToyVLIWDisassembler::getInstruction(MCInst &MI, uint64_t &Size,
                                                 ArrayRef<uint8_t> Bytes,
                                                 uint64_t Address,
                                                 raw_ostream &OS,
                                                 raw_ostream &CS) const {
  CommentStream = &CS;

  Size = 0;
  // We want to read exactly 8 bytes of data.
  if (Bytes.size() < 8)
    return Fail;

  Size = 8;

  // Encoded as a small-endian 64-bit word in the stream.
  const uint64_t Insn = eatBytes<uint64_t>(Bytes);

  // Calling the auto-generated decoder function.
  return decodeInstruction(DecoderTable64, MI, Insn, Address, this, STI);
}

extern "C" void LLVMInitializeToyVLIWDisassembler() {
  TargetRegistry::RegisterMCDisassembler(getTheToyVLIWTarget(),
                                         createToyVLIWDisassembler);
}
