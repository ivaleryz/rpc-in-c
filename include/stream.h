#ifndef STREAMS_H
#define STREAMS_H

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#define STREAM_DEF_SIZE 512

enum { ERROR = -1, SUCCESS = 0 };

typedef struct {
  char *buffer;
  size_t size;
  size_t next;
  size_t checkpoint;
} stream_t;

void stream_init(stream_t **stream);
void stream_init_size(stream_t **stream, const size_t stream_size);

void stream_ser_string(stream_t *stream, const char *data,
                       const size_t data_size);

void stream_des_string(char *buffer, stream_t *stream, const size_t size);

int stream_is_empty(const stream_t *stream);

int stream_insert_offset(stream_t *stream, const char *data,
                         const size_t data_size, const size_t start_offset);

void stream_set_checkpoint(stream_t *stream);
size_t stream_get_checkpoint(const stream_t *stream);

/**
 * @brief Skip number of bytes in stream's buffer
 *
 * @param bytes_skip Number of bytes to skip
 * @note If bytes_skip > 0 - skip forward
 *       If bytes_skip < 0 - skip backward
 */
void stream_skip(stream_t *stream, const int64_t bytes_skip);

void stream_free(stream_t *stream);

#endif
