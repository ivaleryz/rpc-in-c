#include "stream.h"

static void _write_buffer(char *dest, const char *data,
                          const size_t data_size) {
  memcpy(dest, data, data_size);
}

static void _stream_serialize(stream_t *stream, const char *data,
                              const size_t data_size) {
  size_t available_size = stream->size - stream->next;
  bool is_resize = false;

  while (available_size < data_size) {
    stream->size = stream->size * 2;
    available_size = stream->size - stream->next;
    is_resize = true;
  }

  if (is_resize == false) {
    _write_buffer(stream->buffer + stream->next, data, data_size);
    stream->next += data_size;
    return;
  }

  /* resize */
  stream->buffer = realloc(stream->buffer, stream->size);
  assert(stream->buffer != NULL);

  _write_buffer(stream->buffer + stream->next, data, data_size);
  stream->next += data_size;
}

static void _stream_deserialize(char *dest, stream_t *stream, size_t size) {
  _write_buffer(dest, stream->buffer + stream->next, size);

  stream->next += size;
}

void stream_init(stream_t **stream) {
  (*stream) = calloc(1, sizeof(stream_t));
  assert(*stream != NULL);

  (*stream)->buffer = calloc(1, STREAM_DEF_SIZE);
  assert((*stream)->buffer != NULL);

  (*stream)->size = STREAM_DEF_SIZE;

  (*stream)->next = 0;

  (*stream)->checkpoint = 0;
}

void stream_init_size(stream_t **stream, const size_t stream_size) {
  (*stream) = calloc(1, sizeof(stream_t));
  assert(*stream != NULL);

  (*stream)->buffer = calloc(1, stream_size);
  assert((*stream)->buffer != NULL);

  (*stream)->size = stream_size;

  (*stream)->next = 0;

  (*stream)->checkpoint = 0;
}

void stream_ser_string(stream_t *stream, const char *data,
                       const size_t data_size) {
  _stream_serialize(stream, data, data_size);
}

void stream_des_string(char *dest, stream_t *stream, const size_t size) {
  _stream_deserialize(dest, stream, size);
}

int stream_is_empty(const stream_t *stream) {
  assert(stream);

  return (stream->next == 0 ? 0 : (-1));
}

/* Copy 'data' to the stream starting from 'start_offset' position */
int stream_insert_offset(stream_t *stream, const char *data,
                         const size_t data_size, const size_t start_offset) {
  assert(stream);
  assert(data);

  if ((stream->size - stream->next) < data_size) return ERROR;
  if (stream->size < data_size) return ERROR;

  _write_buffer(stream->buffer + start_offset, data, data_size);
  return SUCCESS;
}

void stream_set_checkpoint(stream_t *stream) {
  assert(stream != NULL);

  stream->checkpoint = stream->next;
}

size_t stream_get_checkpoint(const stream_t *stream) {
  assert(stream != NULL);

  return stream->checkpoint;
}

void stream_skip(stream_t *stream, const int64_t bytes_skip) {
  if (bytes_skip >= 0) { /* move forward */
    size_t available_size = stream->size - stream->next;
    bool is_resize = false;

    while (available_size < (size_t)bytes_skip) {
      stream->size = stream->size * 2;
      available_size = stream->size - stream->next;
      is_resize = true;
    }

    if (is_resize == false) {
      stream->next += (size_t)bytes_skip;
      return;
    }

    /* resize */
    stream->buffer = realloc(stream->buffer, stream->size);
    assert(stream->buffer != NULL);

    stream->next += (size_t)bytes_skip;
  } else { /* move backward */
    const int64_t bytes_skip_pos = -(bytes_skip);
    const size_t skip_back = (size_t)(bytes_skip_pos);

    const long over = (long)(stream->next - (size_t)bytes_skip_pos);

    if (over > 0) {
      stream->next -= skip_back;
    } else {
      stream->next -= stream->next;
    }
  }
}

void stream_free(stream_t *stream) {
  if (stream == NULL) return;

  memset(stream->buffer, 0, stream->size);
  free(stream->buffer);

  stream->size = 0;
  stream->next = 0;
  stream->checkpoint = 0;

  free(stream);
}

void stream_copy_in_offset(stream_t *in,
                          const char *data,
                          const size_t data_size,
                          const size_t offset){
  if(offset > in->size){
    return;
  }

  memcpy(in->buffer + offset, data, data_size);
}
