#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "file_io.h"
#include "prediction.h"
#include "encoder.h"
#include "decoder.h"
#include "compression.h"

char *g_data_buf;
char *error;
int *encoded_data;

int block_size = 0;
int file_size = 0;

int main(int argc, char *argv[])
{
	int block_cnt = 0;
	int k = 0;
	int data_remaining = 0;

	if(argc != 3)
	{
		printf("Incorrect input arguments\n");
		printf("Usage: ./codec filename blocksize\n");
		printf("Example: ./codec Samples/test441100.wav 1024\n");
	}
	else
	{
		block_size = atoi(argv[2]);

		/* Error, encoding, decoding and compression is done per block */
		error = (char*) malloc (sizeof(char)*block_size);
		encoded_data = (int*) malloc (sizeof(int)*block_size*2);

		/* Input .wav file */
		file_size = read_file(argv[1]);

		data_remaining = file_size % block_size;
		for(block_cnt=0;block_cnt<(file_size/block_size) || data_remaining;block_cnt++){
			/* Update block size with data remaining if incomplete block */
			if(block_cnt >= (file_size/block_size)){
				block_size = data_remaining;
				data_remaining = 0;
			}

			n_order_predictor(&g_data_buf[block_cnt*block_size], error, block_size, 3);

			k = encode((int*)error, encoded_data, block_size);

			/* Write k and encoded data to file */
			compress(encoded_data, k, block_size);
		}
		
		/* Free up used memory */
		free(g_data_buf);
		free(error);
		free(encoded_data);
	}
	return 0;
}
