#ifndef ENCODE_H
#define ENCODE_H

int encode(char *input_data, int *output_data, int size);
int get_sse(char *e, int block_size);
int get_k(int s_error);

#endif
