#include <stdio.h>

#include "stream.h"
#include "utils.h"

static void test_offset_copy() {
  stream_t *stream = NULL;

  stream_init_size(&stream, 8);

  const char *data = "zZ";

  /* Write the 'data' to the stream on offset 5 */
  stream_insert_offset(stream, data, strlen(data), 5);

  assert(stream->buffer[0] == '\0');
  assert(stream->buffer[1] == '\0');
  assert(stream->buffer[2] == '\0');
  assert(stream->buffer[3] == '\0');
  assert(stream->buffer[4] == '\0');
  assert(stream->buffer[5] == 'z');
  assert(stream->buffer[6] == 'Z');
  assert(stream->buffer[7] == '\0');

  stream_free(stream);
}

int main(void) {
  test_offset_copy();

  return 0;
}
