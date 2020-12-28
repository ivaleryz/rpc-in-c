#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>
#include <stdio.h>

#include "stddef.h"

static inline void dump_memory(const char *data, const size_t size) {
  fprintf(stdout, "\nData in [%p : %p]\n", (void *)data, (void *)(data + size));

  for (size_t i = 0; i < size; ++i) {
    if (i % 16 == 0) fprintf(stdout, "\n");

    fprintf(stdout, "%02X ", ((unsigned int)data[i]));
  }
}

#endif
