#include "crpc_internal.h"

int crpc_release_client(crpc_t *client) {
  int rc = CRPC_OK;

  if (client == NULL || client->type != CRPC_TYPE_CLIENT) {
    rc = CRPC_ERR_INVALID;
    goto ret;
  }

  if (NET_OK != net_release_client_context(client->client)) {
    rc = CRPC_ERR_INVALID;
    goto ret;
  }

  free(client); /* TODO(valery): Implement the safe free function */

ret:
  return rc;
}
