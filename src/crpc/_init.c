#include "crpc_internal.h"

int _crpc_init(crpc_t*        crpc,
               const char*    remote_host,
               const uint16_t remote_port) {
  int rc = CRPC_OK;

  crpc = calloc(1, sizeof(crpc_t));
  if (crpc == NULL) {
    rc = CRPC_ERR_INVALID;
  }

  crpc->client = net_init_client_context(remote_host, remote_port);
  if (crpc->client == NULL) {
    free(crpc); /* TODO(valery): Implement the safe free function */
    rc = CRPC_ERR_INVALID;
  }

  return rc;
}
