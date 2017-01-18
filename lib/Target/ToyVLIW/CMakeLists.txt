set(LLVM_TARGET_DEFINITIONS ToyVLIW.td)

tablegen(LLVM ToyVLIWGenRegisterInfo.inc -gen-register-info)
tablegen(LLVM ToyVLIWGenInstrInfo.inc -gen-instr-info)
tablegen(LLVM ToyVLIWGenAsmWriter.inc -gen-asm-writer)
tablegen(LLVM ToyVLIWGenDAGISel.inc -gen-dag-isel)
tablegen(LLVM ToyVLIWGenCallingConv.inc -gen-callingconv)
tablegen(LLVM ToyVLIWGenSubtargetInfo.inc -gen-subtarget)
tablegen(LLVM ToyVLIWGenMCCodeEmitter.inc -gen-emitter)
tablegen(LLVM ToyVLIWGenDisassemblerTables.inc -gen-disassembler)

add_public_tablegen_target(ToyVLIWCommonTableGen)

add_llvm_target(ToyVLIWCodeGen
  ToyVLIWAsmPrinter.cpp
  ToyVLIWFrameLowering.cpp
  ToyVLIWInstrInfo.cpp
  ToyVLIWIntrinsicInfo.cpp
  ToyVLIWISelDAGToDAG.cpp
  ToyVLIWISelLowering.cpp
  ToyVLIWMCInstLower.cpp
  ToyVLIWRegisterInfo.cpp
  ToyVLIWSelectionDAGInfo.cpp
  ToyVLIWSubtarget.cpp
  ToyVLIWTargetMachine.cpp)

add_subdirectory(AsmParser)
add_subdirectory(Disassembler)
add_subdirectory(InstPrinter)
add_subdirectory(TargetInfo)
add_subdirectory(MCTargetDesc)
