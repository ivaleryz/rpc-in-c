#include "crpc_internal.h"

crpc_t *crpc_create_server(const uint16_t     local_port,
                           server_msg_handler msg_handler) {
  if (msg_handler == NULL) return NULL;

  crpc_t *context = calloc(1, sizeof(crpc_t));
  if (context == NULL) {
    return NULL;
  }

  context->type = CRPC_TYPE_SERVER;
  context->server =
      net_init_server_context("localhost", local_port, msg_handler);
  if (context->server == NULL) {
    return NULL;
  }

  return context;
}
