#ifndef DECODER_H
#define DECODER_H

void decode(char *e, char *buf, int block_size, int k);
int get_encoded_k(char *buf);

#endif
