#include <stdio.h>
#include <string.h>

#include "file.io.h"

void file_read(char *filename, char *filedata)
{
	FILE *input_file = fopen(filename,"r");      

	fclose(input_file);
}

int get_file_size()
{
	return file_size
}

int get_num_samples()
{
	return num_samples;
}
