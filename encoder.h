#ifndef ENCODE_H
#define ENCODE_H

int encode(int *input_data, int *output_data, int size);
int get_sse(int *e, int block_size);
int get_k(int s_error);

#endif
