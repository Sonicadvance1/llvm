add_llvm_library(LLVMToyVLIWDesc
  ToyVLIWAsmBackend.cpp
  ToyVLIWELFObjectWriter.cpp
  ToyVLIWMCAsmInfo.cpp
  ToyVLIWMCCodeEmitter.cpp
  ToyVLIWMCTargetDesc.cpp
  )

add_dependencies(LLVMToyVLIWDesc ToyVLIWCommonTableGen)
