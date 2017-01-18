add_llvm_library(LLVMToyVLIWAsmPrinter
  ToyVLIWInstPrinter.cpp
  )

add_dependencies(LLVMToyVLIWAsmPrinter ToyVLIWCommonTableGen)
