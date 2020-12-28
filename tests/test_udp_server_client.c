#include <assert.h>
#include <pthread.h>
#include <stdatomic.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "../include/network/network.h"

static atomic_bool is_server_finished = false;
static atomic_bool is_client_finished = false;

static int msg_handler(int          sender,
                       void *       buffer,
                       const size_t buffer_size,
                       void *       client_addr) {
  (void)buffer_size;

  const size_t number = *((size_t *)buffer);

  switch (number) {
    case NET_REQ_STOP:
      is_server_finished = true;
      return 1;
      break;

    default:
      net_send_buffer_udp(
          sender,
          (const char *)&(size_t){NET_RES_OK}, /* Is OK status */
          sizeof(size_t),
          client_addr);
      break;
  }

  return 0;
}

static void *run_server(void *arg) {
  (void)arg;

  net_server_cont_t *server =
      net_init_server_context("localhost", 6677, msg_handler);

  net_start_udp_server(server);

  net_release_server_context(server);

  return NULL;
}

static void *run_client(void *arg) {
  (void)arg;

  usleep(10000);

  net_client_cont_t *client = net_init_client_context("localhost", 6677);

  char *response = NULL;
  /* Send ping request */
  net_send_data_udp(client,
                    (const char *)&(size_t){NET_REQ_PING},
                    sizeof(size_t),
                    &response);

  /* Is ping succeess ? */
  size_t number = *((size_t *)response);
  (void)number;
  assert(number == NET_RES_OK);

  /* TODO(valery): Implement safe free function */
  free(response);
  response = NULL;

  /* Send stop the server request */
  net_send_data_udp(client,
                    (const char *)&(size_t){NET_REQ_STOP},
                    sizeof(size_t),
                    &response);

  number = 0;
  number = *((size_t *)response);
  assert(number == NET_RES_OK);

  /* TODO(valery): Implement safe free function */
  free(response);
  response = NULL;

  /* Server was stopped so the client exiting */
  is_client_finished = true;

  net_release_client_context(client);

  return NULL;
}

int main(void) {
  pthread_t srvr, clnt;

  pthread_create(&srvr, NULL, run_server, NULL);
  pthread_create(&clnt, NULL, run_client, NULL);

  pthread_join(srvr, NULL);
  pthread_join(clnt, NULL);

  assert(is_server_finished == true);
  assert(is_client_finished == true);

  fprintf(stdout, "Done!\n");

  return 0;
}
