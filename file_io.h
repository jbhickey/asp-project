#ifndef FILE_H
#define FILE_H

#define BLOCK_SIZE 8

void read_file(char *filename);
void debug_file(char *filename);
long get_file_size(FILE *file);
void read_block(char *data);
void write_block(char *data);
int get_num_samples(char *data);

#endif
