#pragma once

#ifdef _WIN32
#define TR_EXPORT extern "C" __declspec(dllexport)
#else
#define TR_EXPORT extern "C" __attribute__((visibility("default")))
#endif

TR_EXPORT int CalcDecompressedSize(const uint8_t* src, const uint32_t src_size, uint32_t* decompressed_size);
TR_EXPORT int Decompress(const uint8_t* src, const uint32_t src_size, uint8_t** dest, uint32_t* dest_size, uint32_t* decompressed_size);
TR_EXPORT int Compress(const uint8_t* src, const uint32_t src_size, uint8_t** dest, uint32_t* compressed_size);
TR_EXPORT uint8_t* AllocateBuffer(uint32_t buffer_size);
TR_EXPORT void FreeBuffer(uint8_t* buffer);