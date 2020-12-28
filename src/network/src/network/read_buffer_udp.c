#include "network_internal.h"

ssize_t net_read_buffer_udp(const int           read_from,
                            char *              buffer,
                            size_t              buffer_size,
                            struct sockaddr_in *client_addr) {
  return recvfrom(read_from,
                  buffer,
                  buffer_size,
                  0,
                  (struct sockaddr *)client_addr,
                  &(socklen_t){sizeof(struct sockaddr_in)});
}
