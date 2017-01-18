//===-- ToyVLIWAsmBackend.cpp - ToyVLIW Assembler Backend -------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "MCTargetDesc/ToyVLIWMCTargetDesc.h"
#include "MCTargetDesc/ToyVLIWFixupKinds.h"
#include "llvm/ADT/StringSwitch.h"
#include "llvm/MC/MCAsmBackend.h"
#include "llvm/MC/MCAssembler.h"
#include "llvm/MC/MCContext.h"
#include "llvm/MC/MCDirectives.h"
#include "llvm/MC/MCELFObjectWriter.h"
#include "llvm/MC/MCExpr.h"
#include "llvm/MC/MCFixupKindInfo.h"
#include "llvm/MC/MCMachObjectWriter.h"
#include "llvm/MC/MCObjectWriter.h"
#include "llvm/MC/MCSectionELF.h"
#include "llvm/MC/MCSectionMachO.h"
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/MC/MCValue.h"
#include "llvm/Support/ELF.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/MachO.h"
#include "llvm/Support/raw_ostream.h"
using namespace llvm;

namespace {
class ToyVLIWELFObjectWriter : public MCELFObjectTargetWriter {
public:
  ToyVLIWELFObjectWriter(uint8_t OSABI)
      : MCELFObjectTargetWriter(/*Is64Bit*/ true, OSABI, /*ELF::EM_ToyVLIW*/ ELF::EM_TOYVLIW,
                                /*HasRelocationAddend*/ false) {}
};

class ToyVLIWAsmBackend : public MCAsmBackend {
  static const unsigned PCRelFlagVal = MCFixupKindInfo::FKF_IsPCRel;

public:
  ToyVLIWAsmBackend(const Target &T, const StringRef TT) : MCAsmBackend() {}

  ~ToyVLIWAsmBackend() {}

  unsigned getNumFixupKinds() const override {
    return ToyVLIW::NumTargetFixupKinds;
  }
  const MCFixupKindInfo &getFixupKindInfo(MCFixupKind Kind) const override {
    const static MCFixupKindInfo Infos[ToyVLIW::NumTargetFixupKinds] = {
      // This table *must* be in the order that the fixup_* kinds are defined in
      // ToyVLIWFixupKinds.h.
      //
      // Name                           Offset (bits) Size (bits)     Flags
    };

    if (Kind < FirstTargetFixupKind)
      return MCAsmBackend::getFixupKindInfo(Kind);

    assert(unsigned(Kind - FirstTargetFixupKind) < getNumFixupKinds() &&
           "Invalid kind!");
    return Infos[Kind - FirstTargetFixupKind];
  }

  /// processFixupValue - Target hook to process the literal value of a fixup
  /// if necessary.
  void processFixupValue(const MCAssembler &Asm, const MCAsmLayout &Layout,
                         const MCFixup &Fixup, const MCFragment *DF,
                         const MCValue &Target, uint64_t &Value,
                         bool &IsResolved) override {}

  void applyFixup(const MCFixup &Fixup, char *Data, unsigned DataSize,
                  uint64_t Value, bool IsPCRel) const override;

  bool mayNeedRelaxation(const MCInst &Inst) const override { return false; }

  bool fixupNeedsRelaxation(const MCFixup &Fixup, uint64_t Value,
                            const MCRelaxableFragment *DF,
                            const MCAsmLayout &Layout) const override {
    return false;
  }
  void relaxInstruction(const MCInst &Inst, const MCSubtargetInfo &STI,
                        MCInst &Res) const override {}

  bool writeNopData(uint64_t Count, MCObjectWriter *OW) const override {
    if (Count == 0) {
      return true;
    }
    return false;
  }

  unsigned getPointerSize() const { return 8; }
};
} // end anonymous namespace

void ToyVLIWAsmBackend::applyFixup(const MCFixup &Fixup, char *Data,
                                   unsigned DataSize, uint64_t Value,
                                   bool IsPCRel) const {
  llvm_unreachable("unreachable");
}

namespace {

class ELFToyVLIWAsmBackend : public ToyVLIWAsmBackend {
public:
  uint8_t OSABI;
  ELFToyVLIWAsmBackend(const Target &T, const StringRef TT, uint8_t _OSABI)
      : ToyVLIWAsmBackend(T, TT), OSABI(_OSABI) {}

  MCObjectWriter *createObjectWriter(raw_pwrite_stream &OS) const override {
    return createToyVLIWELFObjectWriter(OS, OSABI);
  }
};

} // end anonymous namespace

MCAsmBackend *llvm::createToyVLIWAsmBackend(const Target &T,
                                              const MCRegisterInfo &MRI,
                                              const Triple &TT,
                                              StringRef CPU,
                                              const MCTargetOptions &Options) {
  assert(TT.isOSBinFormatELF() && "Expect either ELF target");
  uint8_t OSABI = MCELFObjectTargetWriter::getOSABI(TT.getOS());
  return new ELFToyVLIWAsmBackend(T, TT.getTriple(), OSABI);
}
