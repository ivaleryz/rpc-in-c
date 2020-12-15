#include <stdio.h>

#include "stream.h"

static void test_checkpoint() {
  stream_t *stream = NULL;

  stream_init_size(&stream, 16);

  stream_ser_string(stream, "test", strlen("test"));

  stream_set_checkpoint(stream);
  const size_t checkpoint = stream_get_checkpoint(stream);

  if (checkpoint != 4) assert(checkpoint == 4);

  stream_free(stream);
}

int main(void) {
  test_checkpoint();

  return 0;
}
