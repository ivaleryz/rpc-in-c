#include "network_internal.h"

int _net_open_udp_socket() { return socket(AF_INET, SOCK_DGRAM, 0); }
