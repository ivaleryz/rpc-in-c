#include "network_internal.h"

net_server_cont_t *net_init_server_context(const char *       host,
                                           const uint16_t     port,
                                           server_msg_handler msg_handler) {
  net_server_cont_t *server = calloc(1, sizeof(net_server_cont_t));
  if (server == NULL) {
    goto bad;
  }

  memset(&server->addr_info, 0, sizeof(server->addr_info));
  server->addr_info.sin_family = AF_INET;
  (void)host; /* TODO(valery): Use host to set s_addr */
  server->addr_info.sin_addr.s_addr = INADDR_ANY;
  server->addr_info.sin_port = htons(port);

  memset(&server->client_addr, 0, sizeof(server->client_addr));

  server->server_msg_handler = msg_handler;

  return server;

bad:
  if (server) free(server);

  return NULL;
}
