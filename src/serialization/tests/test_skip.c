#include <stdio.h>

#include "stream.h"
#include "utils.h"

static void test_skip() {
  /* Test move forward */
  {
    stream_t *stream = NULL;
    stream_init_size(&stream, 16);

    stream_skip(stream, 4);
    assert(stream->next == 4);

    stream_ser_string(stream, "xXxX", strlen("xXxX"));

    stream_skip(stream, 24);
    assert(stream->next == 32);

    stream_ser_string(stream, "xXxX", strlen("xXxX"));
    assert(stream->next == 36);

    stream_free(stream);
  }
  /* Test move backward */
  {
    stream_t *stream = NULL;
    stream_init_size(&stream, 8);

    stream_skip(stream, 4);
    assert(stream->next == 4);

    stream_ser_string(stream, "xX", strlen("xX"));

    stream_skip(stream, (-2));
    assert(stream->next == 4);

    stream_skip(stream, (-8));
    assert(stream->next == 0);

    stream_free(stream);
  }
}

int main(void) {
  test_skip();

  return 0;
}
