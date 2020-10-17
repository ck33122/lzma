cmake_minimum_required(VERSION 3.4)
project(lzma C)

set(sources
  7zAlloc.c
  7zArcIn.c
  7zBuf.c
  7zBuf2.c
  7zCrc.c
  7zCrcOpt.c
  7zDec.c
  7zFile.c
  7zStream.c
  Aes.c
  AesOpt.c
  Alloc.c
  Bcj2.c
  Bra.c
  Bra86.c
  BraIA64.c
  CpuArch.c
  Delta.c
  LzFind.c
  Lzma2Dec.c
  LzmaDec.c
  LzmaEnc.c
  LzmaLib.c
  Sha256.c)

list(TRANSFORM sources PREPEND ${CMAKE_CURRENT_SOURCE_DIR}/src/)

# add_executable(lzma src/Util/7z/7zMain.c ${sources})
add_library(lzma ${sources})
target_include_directories(lzma
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_compile_definitions(lzma PUBLIC -D_7ZIP_ST)
set_target_properties(lzma PROPERTIES
  C_STANDARD 11
  C_STANDARD_REQUIRED TRUE
  C_EXTENSIONS ON
  LINKER_LANGUAGE C)
