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

	printf("opening file\n");

	debug_file = fopen(filename,"r");
	
	if(debug_file == NULL)
       		printf("File error");

	fseek(debug_file,0,SEEK_END);
	printf("seek ok\n");

	file_size = ftell(debug_file);
	printf("file size ok\n");

	rewind(debug_file);
	printf("rewind ok\n");

	buffer = (char*) malloc (sizeof(char)*file_size);
	printf("allocated memory\n");

	fread(buffer,1,file_size,debug_file);
	printf("read file\n");

	printf("%s",buffer);

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
