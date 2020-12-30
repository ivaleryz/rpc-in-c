#include "crpc_internal.h"

int crpc_start_server(crpc_t *context) {
  int rc = CRPC_OK;

  if (context == NULL || context->type != CRPC_TYPE_SERVER) {
    rc = CRPC_ERR_INVALID;
    goto ret;
  }

  if (net_start_udp_server(context->server) != NET_OK) {
    rc = CRPC_ERR_START;
    goto ret;
  }

ret:
  return rc;
}
