#include <stdio.h>

#include "stream.h"

static void test_ser_string() {
  stream_t *stream = NULL;

  stream_init_size(&stream, 8);
  assert(stream->buffer != NULL && "stream->buffer is NULL");

  const char *test_string = "test";
  stream_ser_string(stream, test_string, strlen(test_string));

  const char *test_2 = "aA";
  stream_ser_string(stream, test_2, strlen(test_2));

  /* ... */
  stream->next = 0;

  char buffer[4];
  stream_des_string(buffer, stream, 4);
  assert(0 == memcmp("test", buffer, 4));

  char test_2_buffer[2];
  stream_des_string(test_2_buffer, stream, 2);
  assert(0 == memcmp("aA", test_2_buffer, 2));

  stream_free(stream);
}

static void test_ser_string_resize() {
  stream_t *stream = NULL;

  stream_init_size(&stream, 8);
  assert(stream->buffer != NULL && "stream->buffer is NULL");

  const char *test_string = "testtesttesttesttesttesttesttesttesttestZ";
  stream_ser_string(stream, test_string, strlen(test_string));
  assert(64 == stream->size);

  /* ... */
  stream->next = 0;

  char buffer[41];
  stream_des_string(buffer, stream, 41);

  assert(buffer[41 - 2] == 't');
  assert(buffer[41 - 1] == 'Z');

  stream_free(stream);
}

int main(void) {
  test_ser_string();
  test_ser_string_resize();

  return 0;
}
