#ifndef CRPC_H
#define CRPC_H

#include <network/network.h>
#include <stream.h>

enum {
  CRPC_OK = 0,
  CRPC_ERR_INVALID = -1,
  CRPC_ERR_START = -2,
};

enum { CRPC_TYPE_SERVER, CRPC_TYPE_CLIENT };
typedef struct {
  uint8_t type;
  union {
    net_server_cont_t *server;
    net_client_cont_t *client;
  };

} crpc_t;

crpc_t *crpc_create_server(const uint16_t, server_msg_handler);
crpc_t *crpc_create_client(const char *, const uint16_t);

int crpc_release_server(crpc_t *);
int crpc_release_client(crpc_t *);

int crpc_start_server(crpc_t *context);

int crpc_add(crpc_t *context, const int a, const int b);

#endif
