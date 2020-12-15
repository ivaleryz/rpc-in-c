#include <stdio.h>

#include "stream.h"

static void test_free() {
  stream_t *stream = NULL;

  stream_init(&stream);
  stream_free(stream);

  stream_t *stream_size = NULL;

  stream_init_size(&stream_size, 4096);
  stream_free(stream_size);
}

int main(void) {
  test_free();

  return 0;
}
