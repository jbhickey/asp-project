#ifndef FILE_H
#define FILE_H

int read_file(char *filename);
void write_k(char *filename, int k);
void write_block(char *filename, char *data, int cnt);
long get_file_size(FILE *file);

#endif
