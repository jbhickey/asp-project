#ifndef FILE_H
#define FILE_H

void log_results(int input_file_size, int output_file_size, int block_size, char *filename);
void put_bit(int bit);
void write_byte(char byte, char *filename);
int read_file(char *filename);
int get_file_size(FILE *file);

#endif
