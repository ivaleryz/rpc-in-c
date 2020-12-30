#ifndef RPC_INTERNAL_H
#define RPC_INTERNAL_H

#include "crpc.h"

int _crpc_init(crpc_t*        crpc,
               const char*    remote_host,
               const uint16_t remote_port);

#endif
