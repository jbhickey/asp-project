#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "file_io.h"
#include "prediction.h"
#include "encoder.h"
#include "decoder.h"
#include "compression.h"

void encoding_routine(void);
void decoding_routine(void);

char *g_data_buf;
char *error;
char *encoded_data;
char *decoded_data;
char *compressed_data;
char *decompressed_data;

int block_size = 0;
int file_size = 0;
int write_size = 0;

int main(int argc, char *argv[])
{    	
	if(argc != 3)
	{
		printf("Incorrect input arguments\n");
		printf("Usage: ./codec filename blocksize\n"); 
		printf("Example: ./codec Samples/test441100.wav 1024\n"); 
	}
	else
	{
		block_size = atoi(argv[2]);

		error = (char*) malloc (sizeof(char)*block_size);
		encoded_data = (char*) malloc (sizeof(char)*block_size);
		decoded_data = (char*) malloc (sizeof(char)*block_size);
		compressed_data = (char*) malloc (sizeof(char)*block_size);
		decompressed_data = (char*) malloc (sizeof(char)*block_size);

		/* Input .wav file */
		file_size = read_file(argv[1]);
	
		/* Encode and compress data */
		encoding_routine();
		printf("Encoding complete...\n");		

		/* Output encoded data file */
		file_size = read_file("Output/encoded.out");

		/* Decompress and decode data */
		decoding_routine();		
		printf("Decoding complete...\n");		
				  
		/* Free up used memory */
		free(error);
		free(encoded_data);
		free(decoded_data);
		free(compressed_data);
		free(g_data_buf);
	}
	return 0;
}

void encoding_routine(void)
{		
	int block_cnt = 0;
	int k = 0;
	int data_remaining = 0;

	/* Iterate through full blocks */
	for(block_cnt=0;block_cnt<(file_size/block_size);block_cnt++)
	{
		/* 3rd predictor */
		n_order_predictor(&g_data_buf[block_cnt*block_size], error, block_size, 3);

		/* Write out prediction error */
		write_block("Output/prediction.out", error, block_size);

		/* Encode data */
		k = encode(error, encoded_data, block_size);		

		/* Write encoded data with one byte per sample (no compression) */
		write_k("Output/encoded.out", k);
		write_block("Output/encoded.out", encoded_data, block_size);
	
		/* Compress encoded data */
		write_size = compress(compressed_data, encoded_data, k, block_size);

		/* Write compressed data */
		write_block("Output/compressed.out", compressed_data, write_size);
	}
		
	/* Handle remaining incomplete block */
	data_remaining = file_size % block_size;
	if(data_remaining){
		/* Linear prediction */
		n_order_predictor(&g_data_buf[++block_cnt*block_size], error, data_remaining, 3);
		
		/* Write out prediction error */
		write_block("Output/prediction.out", error, data_remaining);

		/* Encode remaining data */
		k = encode(error, encoded_data, data_remaining);
		
		/* Write encoded data uncompressed */
		write_k("Output/encoded.out", k);
		write_block("Output/encoded.out", encoded_data, data_remaining);			
		
		/* Compress remaining data */
		write_size = compress(compressed_data, encoded_data, k, data_remaining);
		
		/* Write when each byte is full (compressed) */
		write_block("Output/compressed.out", compressed_data, write_size);
	}
}

void decoding_routine(void)
{
	int block_cnt = 0;
	int k = 0;
	int data_remaining = 0;
	int k_offset = 0;

	/* Decompress block */
	decompress(decompressed_data, compressed_data, write_size);

	/* Iterate through full blocks */
	for(block_cnt=0;block_cnt<(file_size/block_size);block_cnt++,k_offset++)
	{
		/* Get k value from global data */
		k = get_encoded_k(&decompressed_data[(block_cnt*block_size)+k_offset]);
			
		/* Decode to error vector */
		decode(decoded_data, &decompressed_data[(block_cnt*block_size)+k_offset+1], block_size, k);
			
		/* Write encoded data to file */
		write_block("Output/decoded.out", decoded_data, block_size);
	}
	
	/* Handle remaining incomplete block */
	data_remaining = file_size % block_size;
	if(data_remaining){		
		k = get_encoded_k(&decompressed_data[block_cnt*block_size]+k_offset);
		
		decode(decoded_data, &g_data_buf[(block_cnt*block_size)+k_offset+1], data_remaining, k);
   		
		write_block("Output/decoded.out", decoded_data, data_remaining);
	}
}
