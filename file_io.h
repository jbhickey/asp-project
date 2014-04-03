#ifndef FILE_H
#define FILE_H

void file_read(char *filename, char *data);
int get_file_size(char *data);
void read_block(char *data);
int get_num_samples(char *data);

#endif
