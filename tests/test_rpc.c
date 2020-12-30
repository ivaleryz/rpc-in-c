#include <assert.h>
#include <network/network.h>
#include <pthread.h>
#include <stdio.h>
#include <stream.h>
#include <unistd.h>

#include "crpc.h"

static int rpc_call_hanlder(int          sender,
                            void *       buffer,
                            const size_t buffer_size,
                            void *       client_addr) {
  fprintf(stdout,
          "[D]: Msg handler: buffer -> %d\n\tbuffer size -> %zu\n\t",
          *((int *)buffer),
          buffer_size);

  stream_t *recv_buff = NULL;
  stream_init_size(&recv_buff, buffer_size);
  memcpy(recv_buff->buffer, buffer, buffer_size);

  int num_one = -1;
  int num_two = -1;
  stream_des_string((char *)&num_one, recv_buff, sizeof(int));
  stream_des_string((char *)&num_two, recv_buff, sizeof(int));
  fprintf(stdout, "[S]: num_one -> %d num_two -> %d\n", num_one, num_two);

  int result = -1;
  result = (num_one + num_two);

  /* Prepare and send response */

  stream_t *response_buff = NULL;
  stream_init_size(&response_buff, sizeof result);
  assert(response_buff->size == sizeof(int));

  stream_ser_string(response_buff, (const char *)&result, sizeof(int));

  net_send_buffer_udp(sender,
                      response_buff->buffer,
                      response_buff->size,
                      client_addr);
  fprintf(stdout, "[D]: Response was sent\n");

  /* Free resources */
  stream_free(recv_buff);
  stream_free(response_buff);

  /**
   * _ONLY_ for debug purpose:
   *  Send response and stop the server
   */

  usleep(50000); /* 0.05 seconds */
  return 1;
}

static void *server_thread(void *arg) {
  (void)arg;

  fprintf(stdout, "[D]: Server thread started\n");

  crpc_t *context = crpc_create_server(8899, rpc_call_hanlder);
  assert(context != NULL);
  assert(context->type == CRPC_TYPE_SERVER);

  crpc_start_server(context);

  int rc = crpc_release_server(context);
  assert(rc == CRPC_OK);

  return NULL;
}

static void *client_thread(void *arg) {
  (void)arg;

  fprintf(stdout, "[D]: Client thread started\n");

  crpc_t *context = crpc_create_client("localhost", 8899);
  assert(context != NULL);

  int rc = crpc_add(context, 5, 10);
  fprintf(stdout, "[D]: Client Thread: rc -> %d\n", rc);
  assert(rc == 15);

  rc = crpc_release_client(context);
  assert(rc == CRPC_OK);

  return NULL;
}

int main(void) {
  pthread_t server, client;

  pthread_create(&server, NULL, server_thread, NULL);
  usleep(5000);
  pthread_create(&client, NULL, client_thread, NULL);

  pthread_join(server, NULL);
  pthread_join(client, NULL);

  fprintf(stdout, "[I]: Done\n");

  return 0;
}
