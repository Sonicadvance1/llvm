//===-- ToyVLIWELFObjectWriter.cpp - ToyVLIW ELF Writer ---------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "MCTargetDesc/ToyVLIWMCTargetDesc.h"
#include "MCTargetDesc/ToyVLIWFixupKinds.h"
#include "llvm/ADT/Statistic.h"
#include "llvm/ADT/StringSwitch.h"
#include "llvm/MC/MCELFObjectWriter.h"
#include "llvm/MC/MCExpr.h"
#include "llvm/MC/MCSectionELF.h"
#include "llvm/MC/MCValue.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

namespace {
  class ToyVLIWELFObjectWriter : public MCELFObjectTargetWriter {
  public:
    ToyVLIWELFObjectWriter(uint8_t OSABI);

    virtual ~ToyVLIWELFObjectWriter();

    unsigned getRelocType(MCContext &Ctx, const MCValue &Target,
                      const MCFixup &Fixup, bool IsPCRel) const override;
  };
}

unsigned ToyVLIWELFObjectWriter::getRelocType(MCContext &Ctx, const MCValue &Target,
                                            const MCFixup &Fixup, bool IsPCRel) const {

  unsigned Type = 0;
  switch ((unsigned)Fixup.getKind()) {
  default:
    llvm_unreachable("Unimplemented");
  }
  return Type;
}

ToyVLIWELFObjectWriter::ToyVLIWELFObjectWriter(uint8_t OSABI)
    : MCELFObjectTargetWriter(/*Is64Bit*/ true, OSABI, /*ELF::EM_ToyVLIW*/ ELF::EM_TOYVLIW,
                              /*HasRelocationAddend*/ false) {}

ToyVLIWELFObjectWriter::~ToyVLIWELFObjectWriter() {}

MCObjectWriter *llvm::createToyVLIWELFObjectWriter(raw_pwrite_stream &OS, uint8_t OSABI) {
  MCELFObjectTargetWriter *MOTW = new ToyVLIWELFObjectWriter(OSABI);
  return createELFObjectWriter(MOTW, OS, /*IsLittleEndian=*/true);
}
