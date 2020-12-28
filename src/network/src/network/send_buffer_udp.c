#include "network_internal.h"

ssize_t net_send_buffer_udp(int                 send_to,
                            const char *        buffer,
                            const size_t        buffer_size,
                            struct sockaddr_in *client_addr) {
  return sendto(send_to,
                buffer,
                buffer_size,
                0,
                (struct sockaddr *)client_addr,
                (socklen_t){sizeof(struct sockaddr_in)});
}
