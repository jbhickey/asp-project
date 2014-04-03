#include <stdio.h>
#include <string.h>

#include "file.io.h"

void file_read(char *filename, char *filedata)
{
	FILE *input_file = fopen(filename,"r");

	// Detect if it's a raw (decoded) file or a compressed (encoded file)
	if(input_file)
	{
		
	}

	fclose(input_file);
}
