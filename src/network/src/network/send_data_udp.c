#include <stdio.h>

#include "network_internal.h"

size_t net_send_data_udp(IN net_client_cont_t* client,
                         IN const char*        data,
                         IN const size_t       data_size,
                         OUT char**            response_buffer) {
  client->server = _net_open_udp_socket();

  net_send_buffer_udp(client->server, data, data_size, &client->server_addr);

  char    buff[NET_MAX_BUFFER_SIZE];
  ssize_t read_bytes = net_read_buffer_udp(client->server,
                                           buff,
                                           NET_MAX_BUFFER_SIZE,
                                           &client->server_addr);
  if (read_bytes == (-1)) {
    perror("Read Buffer: ");
    return 0;
  }

  *response_buffer = calloc(1, (size_t)read_bytes);
  memcpy(*response_buffer, buff, (size_t)read_bytes);

  return (size_t)read_bytes;
}
