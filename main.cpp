#include <cstdarg>
#include <cstring>
#include <iostream>

#include "lzx/lzx.h"
#include "main.h"

int CalcDecompressedSize(const uint8_t* src, const uint32_t src_size, uint32_t* decompressed_size) 
{
    return lzx_calc_decompress_size(src, src_size, decompressed_size);
}

int Decompress(const uint8_t* src, const uint32_t src_size, uint8_t** dest, uint32_t* decompressed_size)
{
    uint8_t* buffer = nullptr;
    int result = lzx_decompress(src, src_size, &buffer, 0, decompressed_size);
    *dest = buffer; 
    return result;
}

int Compress(const uint8_t* src, const uint32_t src_size, uint8_t** dest, uint32_t* compressed_size)
{
    uint8_t* buffer = nullptr;
    int result = lzx_compress(src, src_size, &buffer, compressed_size);
    *dest = buffer; 
    return result;
}

int FreeBuffer(uint8_t* buffer)
{
    free(buffer);
    return 0;
}
