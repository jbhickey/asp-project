#ifndef FILE_H
#define FILE_H

int read_file(char *filename);
void debug_file(char *filename);
long get_file_size(FILE *file);
void write_block(char *filename, char *data, int block_size);
int get_num_samples(char *data);

#endif
