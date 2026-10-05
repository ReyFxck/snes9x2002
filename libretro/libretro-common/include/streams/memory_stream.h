/* Copyright  (C) 2010-2020 The RetroArch team
 *
 * ---------------------------------------------------------------------------------------
 * The following license statement only applies to this file (memory_stream.h).
 * ---------------------------------------------------------------------------------------
 *
 * Permission is hereby granted, free of charge,
 * to any person obtaining a copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef _LIBRETRO_SDK_FILE_MEMORY_STREAM_H
#define _LIBRETRO_SDK_FILE_MEMORY_STREAM_H

#include <stdint.h>
#include <stddef.h>

#include <retro_common_api.h>

RETRO_BEGIN_DECLS

typedef struct memstream memstream_t;

/*
 * RetroArch also exports memstream_* symbols, but its bundled implementation
 * may use a different API. A statically linked PS2 core must therefore keep
 * its private memory-stream implementation under unique symbol names.
 */
#if defined(PS2)
#define memstream_open      s9x2002_memstream_open
#define memstream_close     s9x2002_memstream_close
#define memstream_read      s9x2002_memstream_read
#define memstream_write     s9x2002_memstream_write
#define memstream_getc      s9x2002_memstream_getc
#define memstream_putc      s9x2002_memstream_putc
#define memstream_gets      s9x2002_memstream_gets
#define memstream_pos       s9x2002_memstream_pos
#define memstream_get_size  s9x2002_memstream_get_size
#define memstream_rewind    s9x2002_memstream_rewind
#define memstream_seek      s9x2002_memstream_seek
#define memstream_get_ptr   s9x2002_memstream_get_ptr
#endif

memstream_t *memstream_open(uint8_t *data, uint64_t size, unsigned writing);

void memstream_close(memstream_t *stream);

uint64_t memstream_read(memstream_t *stream, void *data, uint64_t bytes);

uint64_t memstream_write(memstream_t *stream, const void *data, uint64_t bytes);

int memstream_getc(memstream_t *stream);

void memstream_putc(memstream_t *stream, int c);

char *memstream_gets(memstream_t *stream, char *s, size_t len);

uint64_t memstream_pos(memstream_t *stream);

uint64_t memstream_get_size(memstream_t *stream);

void memstream_rewind(memstream_t *stream);

int64_t memstream_seek(memstream_t *stream, int64_t offset, int whence);

uint64_t memstream_get_ptr(memstream_t *stream);

RETRO_END_DECLS

#endif
