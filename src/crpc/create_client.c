#include "crpc_internal.h"

crpc_t *crpc_create_client(const char *   remote_host,
                           const uint16_t remote_port) {
  crpc_t *context = NULL;

  if (remote_host == NULL) {
    goto ret;
  }

  context = calloc(1, sizeof(crpc_t));
  if (context == NULL) {
    goto ret;
  }

  context->type = CRPC_TYPE_CLIENT;
  context->client = net_init_client_context(remote_host, remote_port);
  if (context->client == NULL) {
    free(context);
    context = NULL;
    goto ret;
  }

ret:
  return context;
}
