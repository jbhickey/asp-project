#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file_io.h"

extern char *g_data_buf;

int read_file(char *filename)
{
	FILE *input_file;
	long input_file_size = 0;
	
	printf("Reading file....\n");

	input_file = fopen(filename,"r");      
	
	if(input_file == NULL)
		printf("File error\n");
	
	input_file_size = get_file_size(input_file);
	
	g_data_buf = (char*) malloc (sizeof(char)*input_file_size);

	fread(g_data_buf,1,input_file_size,input_file);

	fclose(input_file);
	
	return input_file_size;
}
 
void debug_file(char *filename)
{
	FILE *debug_file;
	char *tmp_buf;
	long file_size = 0;
	int i = 0;

	printf("Opening file to debug....\n");

	debug_file = fopen(filename,"r");
	
	if(debug_file == NULL)
       		printf("File error\n");	
	
	file_size = get_file_size(debug_file); 

	printf("File size: %ld bytes\n",file_size);	
	
	tmp_buf = (char*) malloc (sizeof(char)*file_size);

	fread(tmp_buf,1,file_size,debug_file);

	for(i=0;i<file_size;i++)
		printf("%c",tmp_buf[i]);

	fclose(debug_file);
	free(tmp_buf);
}

long get_file_size(FILE *file)
{
	long size = 0;

	// Set pointer to EOF
	fseek(file,0,SEEK_END); 

	// Get position in file
	size = ftell(file); 

	// Reset file pointer?
	rewind(file); 

	return size;
}

void write_block(char *filename, char *data, int block_size)
{
	FILE* output_file;
	int i = 0;
	
	output_file = fopen(filename, "a"); // Open file for appending
	
	for(i=0;i<block_size;i++)
		fprintf(output_file,"%c",data[i]);
	
	printf("Block written....\n");

	fclose(output_file);

	/*
	  Get number of samples to find which block
	  will be the final based off the BLOCK_SIZE

	  if(block_cnt == final_block)
	          free(g_data_buf);
	*/
}

int get_num_samples(char *data)
{
	int num_samples = 0;

	return num_samples;
}
