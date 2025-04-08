#include <cstdarg>
#include <cstring>
#include <iostream>

#include "lzx/lzx.h"
#include "main.h"

int CalcDecompressedSize(const uint8_t* src, const uint32_t src_size, uint32_t* decompressed_size) 
{
    return lzx_calc_decompress_size(src, src_size, decompressed_size);
}

int Decompress(const uint8_t* src, const uint32_t src_size, uint8_t* dest, uint32_t* decompressed_size)
{
    const uint8_t* src_ptr = NULL;
    uint8_t* dest_ptr = NULL;
    LZX_DECODER_CONTEXT* context = NULL;
    uint32_t bytes_decompressed = 0;
    uint32_t bytes_compressed = 0;
    uint32_t total_decompressed_size = 0;
    int result = 0;

    context = lzx_create_decompression();
    if (context == NULL) {
        result = LZX_ERROR_OUT_OF_MEMORY;
        goto Cleanup;
    }

    src_ptr = src;
    dest_ptr = dest;

    for (;;) {
        if ((uint32_t)(src_ptr - src) >= src_size) {
            result = 0;
            break;
        }

        result = lzx_decompress_next_block(context, &src_ptr, &bytes_compressed, &dest_ptr, &bytes_decompressed);
        if (result != 0) {
            goto Cleanup;
        }

        total_decompressed_size += bytes_decompressed;
    }

    if (decompressed_size != NULL) {
        *decompressed_size = total_decompressed_size;
    }
        
Cleanup:

    if (context != NULL) {
        lzx_destroy_decompression(context);
        context = NULL;
    }

    return result;
}

int Compress(const uint8_t* src, const uint32_t src_size, uint8_t* dest, uint32_t* compressed_size)
{
    const uint8_t* src_ptr = NULL;
    ENCODER_CONTEXT* context = NULL;
    uint32_t bytes_read = 0;
    uint32_t bytes_remaining = 0;
    uint32_t total_compressed_size = 0;
    int result = 0;

    // Create the compression context
    context = lzx_create_compression(dest);
    if (context == NULL) {
        result = LZX_ERROR_OUT_OF_MEMORY;
        goto Cleanup;
    }

    bytes_remaining = src_size;
    src_ptr = src;
    
    lzx_flush_compression(context);

    for (;;) {
        if ((uint32_t)(src_ptr - src) >= src_size) {
            result = 0;
			break;
        }
		
        bytes_read = LZX_CHUNK_SIZE < bytes_remaining ? LZX_CHUNK_SIZE : bytes_remaining;

        result = lzx_compress_next_block(context, &src_ptr, bytes_read, &bytes_remaining);
        if (result != 0) {
            goto Cleanup;
        }
    }

    lzx_flush_compression(context);

    total_compressed_size = context->output_buffer_size;

    if (compressed_size != NULL) {
        *compressed_size = total_compressed_size;
    }

Cleanup:
    
    if (context != NULL) {
        lzx_destroy_compression(context);
        context = NULL;
    }

    return result;
}