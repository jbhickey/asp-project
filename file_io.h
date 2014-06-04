#ifndef FILE_H
#define FILE_H

void write_byte(char byte, char *filename);
int read_file(char *filename);
int get_file_size(FILE *file);

#endif
