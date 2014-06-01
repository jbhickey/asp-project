#ifndef ENCODE_H
#define ENCODE_H

int encode(char *e, char *buf, int block_size);
int get_sse(char *e, int block_size);
int get_k(int s_error);

#endif
