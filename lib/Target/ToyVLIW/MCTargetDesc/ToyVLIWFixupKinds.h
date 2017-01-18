//===-- ToyVLIWFixupKinds.h - ToyVLIW Specific Fixup Entries ----*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#pragma once

#include "llvm/MC/MCFixup.h"

namespace llvm {
namespace ToyVLIW {

enum Fixups {
  // XXX: Set the first fixup to FirstTargetFixupKind

  // Marker
  LastTargetFixupKind = FirstTargetFixupKind,
  NumTargetFixupKinds = LastTargetFixupKind - FirstTargetFixupKind
};

} // end namespace ToyVLIW
} // end namespace llvm
