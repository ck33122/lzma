#pragma once
#include <stddef.h>
#include <stdint.h>

typedef struct ISzAlloc ISzAlloc;
typedef const ISzAlloc *ISzAllocPtr;

struct ISzAlloc {
  void *(*Alloc)(ISzAllocPtr p, size_t size);
  void (*Free)(ISzAllocPtr p, void *address); /* address can be 0 */
};

typedef int SRes;

typedef enum { SZ_SEEK_SET = 0, SZ_SEEK_CUR = 1, SZ_SEEK_END = 2 } ESzSeek;

typedef struct ILookInStream ILookInStream;
struct ILookInStream {
  SRes (*Look)(const ILookInStream *p, const void **buf, size_t *size);
  /* if (input(*size) != 0 && output(*size) == 0) means end_of_stream.
     (output(*size) > input(*size)) is not allowed
     (output(*size) < input(*size)) is allowed */
  SRes (*Skip)(const ILookInStream *p, size_t offset);
  /* offset must be <= output(*size) of Look */

  SRes (*Read)(const ILookInStream *p, void *buf, size_t *size);
  /* reads directly (without buffer). It's same as ISeqInStream::Read */
  SRes (*Seek)(const ILookInStream *p, int64_t *pos, ESzSeek origin);
};

typedef struct {
  uint32_t Low;
  uint32_t High;
} CNtfsFileTime;

typedef struct {
  unsigned char *Defs; /* MSB 0 bit numbering */
  uint32_t *Vals;
} CSzBitUi32s;

typedef struct {
  unsigned char *Defs; /* MSB 0 bit numbering */
  // UInt64 *Vals;
  CNtfsFileTime *Vals;
} CSzBitUi64s;

typedef struct {
  uint32_t NumPackStreams;
  uint32_t NumFolders;

  uint64_t *PackPositions; // NumPackStreams + 1
  CSzBitUi32s FolderCRCs;  // NumFolders

  size_t *FoCodersOffsets;                // NumFolders + 1
  uint32_t *FoStartPackStreamIndex;       // NumFolders + 1
  uint32_t *FoToCoderUnpackSizes;         // NumFolders + 1
  unsigned char *FoToMainUnpackSizeIndex; // NumFolders
  uint64_t *CoderUnpackSizes;             // for all coders in all folders

  unsigned char *CodersData;
} CSzAr;

typedef struct {
  CSzAr db;

  uint64_t startPosAfterHeader;
  uint64_t dataPos;

  uint32_t NumFiles;

  uint64_t *UnpackPositions; // NumFiles + 1
  // unsigned char *IsEmptyFiles;
  unsigned char *IsDirs;
  CSzBitUi32s CRCs;

  CSzBitUi32s Attribs;
  // CSzBitUi32s Parents;
  CSzBitUi64s MTime;
  CSzBitUi64s CTime;

  uint32_t *FolderToFile; // NumFolders + 1
  uint32_t *FileToFolder; // NumFiles

  size_t *FileNameOffsets;  /* in 2-byte steps */
  unsigned char *FileNames; /* UTF-16-LE */
} CSzArEx;
