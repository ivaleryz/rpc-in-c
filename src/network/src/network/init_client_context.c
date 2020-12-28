#include "network_internal.h"

net_client_cont_t *net_init_client_context(const char *   host,
                                           const uint16_t port) {
  net_client_cont_t *client = calloc(1, sizeof(net_client_cont_t));
  if (client == NULL) {
    goto bad;
  }

  memset(&client->server_addr, 0, sizeof(client->server_addr));
  client->server_addr.sin_family = AF_INET;
  client->server_addr.sin_port = htons(port);
  inet_pton(AF_INET, host, &client->server_addr.sin_addr);

  return client;

bad:
  if (client) free(client);
  return NULL;
}
