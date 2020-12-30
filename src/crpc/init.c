#include "crpc_internal.h"

int crpc_init(crpc_t*        crpc,
              const char*    remote_host,
              const uint16_t remote_port) {
  if (remote_host == NULL) return CRPC_ERR_INVALID;

  return _crpc_init(crpc, remote_host, remote_port);
}
