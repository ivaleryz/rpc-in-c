#include <stdio.h>

#include "stream.h"

static void test_stream_init() {
  stream_t *stream = NULL;

  stream_init(&stream);

  assert(stream->buffer != NULL && "stream->buffer is NULL");
  assert(stream->size == STREAM_DEF_SIZE);
  assert(stream->next == 0);

  stream_free(stream);
}

static void test_stream_init_size() {
  stream_t *stream = NULL;

  stream_init_size(&stream, 64);

  assert(stream->buffer != NULL && "stream->buffer is NULL");
  assert(stream->size == 64);
  assert(stream->next == 0);

  stream_free(stream);
}

int main(void) {
  test_stream_init();
  test_stream_init_size();

  return 0;
}
