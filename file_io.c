#include <stdio.h>
#include <string.h>

#include "file_io.h"

void file_read(char *filename, char *filedata)
{
	FILE *input_file = fopen(filename,"r");      

	fclose(input_file);
}

int get_file_size(char *data)
{
	int file_size = 0;

	return file_size;
}

void read_block(char *data)
{

}

int get_num_samples(char *data)
{
	int num_samples = 0;

	return num_samples;
}
