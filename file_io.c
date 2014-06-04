#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file_io.h"

extern char *g_data_buf;

void log_results(int input_file_size, int output_file_size, int block_size, char *filename)
{
	FILE *log_file;	
	
	log_file = fopen(filename,"a");
	
	fprintf(log_file,"%d,%d,%d,\n",input_file_size, output_file_size, block_size);

	fclose(log_file);
}

/* Put bit on "stack" */
void put_bit(int bit)
{	
	static char byte = 0;
	static char buffered_bits = 0;

	if(bit){
		byte |= (0x80 >> buffered_bits);
	}
	buffered_bits++;
	
	if(buffered_bits == 8){
		write_byte(byte, "Output/compressed.out");
		buffered_bits = 0;
		byte = 0;
	}
}

void write_byte(char byte, char *filename)
{
	FILE *output_file;

	output_file = fopen(filename,"a");
	
	fprintf(output_file,"%c",byte);

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
