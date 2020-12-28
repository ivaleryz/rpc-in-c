#include "network_internal.h"

ssize_t _net_send_buffer_udp(IN int          receiver,
                             IN const char*  buffer,
                             IN const size_t buffer_size) {
  return sendto(receiver, buffer, buffer_size, MSG_NOSIGNAL, NULL, 0);
}
