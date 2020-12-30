#include "crpc_internal.h"

int crpc_release_server(crpc_t *server) {
  int rc = CRPC_OK;

  if (server == NULL || server->type != CRPC_TYPE_SERVER) {
    rc = CRPC_ERR_INVALID;
    goto ret;
  }

  if (NET_OK != net_release_server_context(server->server)) {
    rc = CRPC_ERR_INVALID;
    goto ret;
  }

  free(server); /* TODO(valery): Implement the safe free function */

ret:
  return rc;
}
