#include <cstdarg>
#include <cstring>
#include <iostream>

#include "lzx/lzx.h"
#include "main.h"

int CalcDecompressedSize(const uint8_t* src, const uint32_t src_size, uint32_t* decompressed_size) 
{
    return lzx_calc_decompress_size(src, src_size, decompressed_size);
}

int Decompress(const uint8_t* src, const uint32_t src_size, uint8_t** dest, uint32_t* dest_size, uint32_t* decompressed_size)
{
    return lzx_decompress(src, src_size, dest, dest_size, decompressed_size);
}

int Compress(const uint8_t* src, const uint32_t src_size, uint8_t** dest, uint32_t* compressed_size)
{
    return lzx_compress(src, src_size, dest, compressed_size);
}

uint8_t* AllocateBuffer(uint32_t buffer_size)
{
    return (uint8_t*)malloc(buffer_size);
}

void FreeBuffer(uint8_t* buffer)
{
    free(buffer);
}
