#include "network_internal.h"

int _net_stop_udp_server(net_server_cont_t *server) {
  int rc = NET_OK;

  if (close(server->listener) == (-1)) {
    rc = NET_ERR_STOP;
  }

  return rc;
}
