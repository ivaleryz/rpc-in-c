#include "network_internal.h"

int _net_release_client_context(net_client_cont_t *client) {
  memset(&client->server_addr, 0, sizeof(client->server_addr));

  /* TODO(valery): Implement safe free function */
  free(client);

  return NET_OK;
}
