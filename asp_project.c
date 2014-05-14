#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "file_io.h"
#include "prediction.h"
#include "encoder.h"

char *g_data_buf;

int main(int argc, char *argv[])
{    
	char error[BLOCK_SIZE] = {0};
	char write_buf[BLOCK_SIZE] = {0};
	int file_size = 0;
	int block_cnt = 0;

	// Filename as argument 
	file_size = read_file(argv[1]);

	// Write specifications to output file

	// Iterate through input data
	for(block_cnt=0;block_cnt<file_size/BLOCK_SIZE;block_cnt++)
	{
		// Nth order avg predictor hence error[n-1]
		avg_predictor(&g_data_buf[block_cnt*BLOCK_SIZE], &error[0]);
		
		// Encode error vector
		encode(&error[0],&write_buf[0]);

		// Write encoded data to file
		write_block(&write_buf[0]);
				
		// Clear write buffer
		memset(&write_buf[0], 0x00, strlen(&write_buf[0]));
	}

	return 0;
}


