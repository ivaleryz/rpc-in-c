#include "network_internal.h"

int net_release_client_context(net_client_cont_t *client) {
  if (client == NULL) return NET_ERR_INVALID;

  return _net_release_client_context(client);
}
