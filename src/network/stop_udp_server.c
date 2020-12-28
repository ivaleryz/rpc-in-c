#include "network_internal.h"

int net_stop_udp_server(net_server_cont_t *server){
    if(server == NULL) return NET_ERR_INVALID;

    return _net_stop_udp_server(server);
}
