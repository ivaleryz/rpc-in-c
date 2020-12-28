#include <arpa/inet.h>
#include <ctype.h>
#include <netinet/in.h>
#include <stdio.h>
#include <sys/socket.h>

#include "network_internal.h"

int net_start_udp_server(net_server_cont_t *server) {
  /* Create UDP socket */
  server->listener = _net_open_udp_socket();
  if (server->listener == (-1)) {
    goto bad;
  }

  if (bind(server->listener,
           (struct sockaddr *)&server->addr_info,
           sizeof(struct sockaddr_in)) == (-1)) {
    perror("Bind: ");
    goto bad;
  }

  /* Data Exchange */
  char buf[NET_BUFFER_SIZE];
  for (;;) {
    ssize_t read_bytes = net_read_buffer_udp(server->listener,
                                             buf,
                                             NET_BUFFER_SIZE,
                                             &server->client_addr);
    if (read_bytes == 0) {
      fprintf(stdout, "[D]: GOT: EOF\n");
      goto bad;
    } else if (read_bytes == (-1)) {
      perror("Data exchange: ");
      goto bad;
    }

    int rc = server->server_msg_handler(server->listener,
                                        buf,
                                        (size_t)read_bytes,
                                        &server->client_addr);
    if (rc == 1) { /* Stop the server */

      net_send_buffer_udp(server->listener,
                          (const char *)&(size_t){NET_RES_OK},
                          sizeof(size_t),
                          &server->client_addr);
      break;
    }
  }

  return NET_OK;
bad:
  if (server->listener) close(server->listener);
  return (-1);
}
