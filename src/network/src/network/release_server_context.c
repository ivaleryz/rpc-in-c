#include "network_internal.h"

int net_release_server_context(net_server_cont_t *server) {
  if (server == NULL) return NET_ERR_INVALID;

  return _net_release_server_context(server);
}
