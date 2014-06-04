#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file_io.h"

extern char *g_data_buf;

void write_byte(char byte, char *filename)
{
	FILE *output_file;

	output_file = fopen(filename,"a");
	
	fprintf("%c",byte);

	fclose(output_file);
}

int read_file(char *filename)
{
	FILE *input_file;
	long input_file_size = 0;

	printf("Reading file....\n");

	input_file = fopen(filename,"r");      

	printf("Filename: %s\n",filename);

	if(input_file == NULL)
		printf("File error\n");
	
	input_file_size = get_file_size(input_file);
	
	g_data_buf = (char*) malloc (sizeof(char)*input_file_size);

	fread(g_data_buf,1,input_file_size,input_file);
	
	fclose(input_file);
	
	return input_file_size;
}

int get_file_size(FILE *file)
{
	int size = 0;

	// Set pointer to EOF
	fseek(file,0,SEEK_END); 

	// Get position in file
	size = ftell(file); 

	// Reset file pointer?
	rewind(file); 

	return size;
}
