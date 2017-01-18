add_llvm_library(LLVMToyVLIWDisassembler
  ToyVLIWDisassembler.cpp
  )

add_dependencies(LLVMToyVLIWDisassembler ToyVLIWCommonTableGen)
