#ifndef NETWORK_NETWORK_INTERNAL_H
#define NETWORK_NETWORK_INTERNAL_H

#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdint.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include "network.h"

#define NET_MAX_BUFFER_SIZE 1024

int _net_open_udp_socket();
int _net_bind_socket(const int sock, const uint32_t addr, const uint16_t port);

ssize_t _net_read_buffer_udp(IN const int sender, IN char *buffer);
ssize_t _net_send_buffer_udp(IN int          receiver,
                             IN const char * buffer,
                             IN const size_t buffer_size);

int _net_close_socket(const int sock);

int _net_stop_udp_server(net_server_cont_t *);

int _net_release_server_context(net_server_cont_t *);

int _net_release_client_context(net_client_cont_t *);

#endif
