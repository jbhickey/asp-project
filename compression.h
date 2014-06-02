#ifndef COMPRESS_H
#define COMPRESS_H

int compress(char *c_data, char *e, int k, int block_size);
void decompress(char *d_data, char *c_data, int size);

#endif
