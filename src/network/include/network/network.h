#ifndef NETWORK_NETWORK_H
#define NETWORK_NETWORK_H

/* TODO(valery): Add Doxygen comments */

#include <netinet/in.h>
#include <stdint.h>
#include <stdlib.h>

#define NET_BUFFER_SIZE 1024

#define IN
#define OUT

enum {
  NET_REQ_PING = 0x400,
  NET_REQ_STOP = 0x404,
  NET_RES_OK = 0x460,
};

enum {
  NET_OK = 0,
  NET_ERR_BIND = -1,
  NET_ERR_INVALID = -2,
  NET_ERR_STOP = -3,
};

typedef int (*server_msg_handler)(int, void *, const size_t, void *);
typedef struct {
  int                listener; /* listener socket */
  int                port;
  struct sockaddr_in addr_info;
  struct sockaddr_in client_addr;
  server_msg_handler server_msg_handler;

} net_server_cont_t;

typedef struct {
  int                server; /* server socket */
  struct sockaddr_in server_addr;
} net_client_cont_t;

net_server_cont_t *net_init_server_context(IN const char *,
                                           IN const uint16_t,
                                           IN       server_msg_handler);
net_client_cont_t *net_init_client_context(IN const char *, IN const uint16_t);

int net_release_server_context(net_server_cont_t *);
int net_release_client_context(net_client_cont_t *);

int net_start_udp_server(net_server_cont_t *);
int net_stop_udp_server(net_server_cont_t *);

/* TODO(valery): Should be internal with prefix _*/
ssize_t net_send_buffer_udp(IN int,
                            IN const char *,
                            IN const size_t,
                            IN struct sockaddr_in *);

/* TODO(valery): Should be internal with prefix _*/
ssize_t net_read_buffer_udp(IN const int,
                            OUT char *,
                            IN const size_t,
                            IN struct sockaddr_in *);

/* Send data with response */
size_t net_send_data_udp(IN net_client_cont_t *,
                         IN const char *,
                         IN const size_t,
                         OUT char **);

void stub();

#endif
