#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file_io.h"

void file_read(char *filename, char *filedata)
{
	FILE *input_file = fopen(filename,"r");      
	
	fclose(input_file);
}

void debug_file(char *filename)
{
	FILE *debug_file;
	char *buffer;
	long file_size = 0;
	int i = 0;

	printf("Opening file....\n");

	debug_file = fopen(filename,"r");
	
	if(debug_file == NULL)
       		printf("File error");

	fseek(debug_file,0,SEEK_END);

	file_size = ftell(debug_file);
	printf("File size: %ld bytes\n",file_size);

	rewind(debug_file);

	buffer = (char*) malloc (sizeof(char)*file_size);

	fread(buffer,1,file_size,debug_file);

	for(i=0;i<file_size;i++)
		printf("%c",buffer[i]);

	fclose(debug_file);
	free(buffer);
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
