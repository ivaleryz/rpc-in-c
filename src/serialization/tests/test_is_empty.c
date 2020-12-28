#include <stdio.h>

#include "stream.h"

static void test_stream_is_empty() {
  stream_t *stream = NULL;

  stream_init(&stream);

  assert(stream->buffer != NULL && "stream->buffer is NULL");
  assert(stream->size == STREAM_DEF_SIZE);
  assert(stream->next == 0);

  assert(0 == stream_is_empty(stream));

  const char *str = "strZ";
  stream_ser_string(stream, str, strlen(str));
  assert((-1) == stream_is_empty(stream));

  stream_free(stream);
}

int main(void) {
  test_stream_is_empty();

  return 0;
}
