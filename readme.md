# lzma

## about

This project is small subset of LZMA SDK with crossplatform setup under CMake.  
It only allows to read 7z archive from disk.

## LZMA SDK license

7z ANSI-C Decoder is part of the LZMA SDK.  
LZMA SDK is written and placed in the public domain by Igor Pavlov.

## installation

Add remote to get ckristen packages from bintray:
```conan remote add ckristen https://api.bintray.com/conan/ckristen/conan```

Add dependency to your project:
```lzma/1.0@ckristen/master```