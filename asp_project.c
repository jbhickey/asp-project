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
char *encoded_data;
char *decoded_data;
char *compressed_data;

int main(int argc, char *argv[])
{    
	int block_size = 0;
	int file_size = 0;
	int write_size = 0;
	int block_cnt = 0;
	int k = 0;
	int data_remaining;
	
	if(argc != 3)
	{
		printf("Incorrect input arguments\n");
		printf("Usage: ./codec filename blocksize\n"); 
		printf("Example: ./codec Samples/test441100.wav 1024\n"); 
	}
	else
	{
		block_size = atoi(argv[2]);

		encoded_data = (char*) malloc (sizeof(char)*block_size);
		decoded_data = (char*) malloc (sizeof(char)*block_size);
		compressed_data = (char*) malloc (sizeof(char)*block_size);
		
		/* Filename as argument */
		file_size = read_file(argv[1]);

		/* Iterate through input data */
		for(block_cnt=0;block_cnt<(file_size/block_size);block_cnt++)
		{
			/* 0.5s[n] - 0.5s[n-1]? */
			//avg_predictor(&g_data_buf[block_cnt*block_size], error, block_size);
			
			/* Encode data */
			k = encode(&g_data_buf[block_cnt*block_size], encoded_data, block_size);
			
			/* Write encoded data with one byte per sample (no compression) */
			write_k("Output/encoded.out", k);
			write_block("Output/encoded.out", encoded_data, block_size);
	
			/* Compress encoded data */
			write_size = compress(compressed_data, encoded_data, k, block_size);

			/* Write compressed data */
			write_block("Output/compressed.out", compressed_data, write_size);
		}
		
		/* Get number of remaining bytes */
		data_remaining = file_size % block_size;

		if(data_remaining){
			/* Encode remaining data */
			k = encode(&g_data_buf[block_cnt*block_size], encoded_data, data_remaining);
			
			/* Write encoded data uncompressed */
			write_k("Output/encoded.out", k);
			write_block("Output/encoded.out", encoded_data, data_remaining);			
		
			/* Compress remaining data */
			write_size = compress(compressed_data, encoded_data, k, data_remaining);

			/* Write when each byte is full (compressed) */
			write_block("Output/compressed.out", compressed_data, write_size);
		}

		printf("Operation complete...\n");		
		  
		/* Free up used memory */
		free(encoded_data);
		free(decoded_data);
		free(compressed_data);
		free(g_data_buf);
	}
	return 0;
}


