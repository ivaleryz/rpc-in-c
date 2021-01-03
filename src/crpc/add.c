#include <stdio.h>

#include "crpc_internal.h"

static const uint8_t ADD_CALL_ARG_NUM = 2;

/* TODO(valery): refactoring */

int crpc_add(crpc_t *context, const int a, const int b) {
  (void)context;
  (void)b;

  const size_t data_size = ADD_CALL_ARG_NUM * sizeof(int);

  stream_t *argument_buff = NULL;
  stream_init_size(&argument_buff, ADD_CALL_ARG_NUM * sizeof(int));

  stream_ser_string(argument_buff, (const char *)&a, sizeof(int));
  stream_ser_string(argument_buff, (const char *)&b, sizeof(int));

  stream_t *send_buffer = NULL;
  stream_init_size(&send_buffer, data_size + sizeof(crpc_hdr_t));
  crpc_hdr_t rpc_hdr = {.type = CRPC_TYPE_ADD,
                        .data_size = argument_buff->size};

  /* Copy RPC Header */
  stream_copy_in_offset(send_buffer,
                        (const char *)&rpc_hdr,
                        sizeof(crpc_hdr_t),
                        0);

  /* Copy Argument buffer */
  stream_copy_in_offset(send_buffer,
                        argument_buff->buffer,
                        argument_buff->size,
                        sizeof(crpc_hdr_t));

  char * resp_buff = NULL;
  size_t resp_buff_size = net_send_data_udp(context->client,
                                            send_buffer->buffer,
                                            send_buffer->size,
                                            &resp_buff);

  fprintf(stdout, "[D]: read_bytes -> %zu\n", resp_buff_size);
  if (resp_buff) {
    fprintf(stdout, "[D]: There is the response\n");
  }

  stream_t *recv_buffer = NULL;
  stream_init_size(&recv_buffer, resp_buff_size);
  memcpy(recv_buffer->buffer, resp_buff, resp_buff_size);

  int num = 0;
  stream_des_string((char *)&num, recv_buffer, sizeof(int));

  fprintf(stdout, "[D]: response -> %d\n", num);

  /* Release resources */
  stream_free(argument_buff);
  stream_free(send_buffer);
  stream_free(recv_buffer);

  free(resp_buff);

  return num;
}
