#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "encoder.h"
#include "decoder.h"

char *sample_data;
char *encoded_data;
char *decoded_data;

int k = 0;

int main(int argc, char *argv[])
{    	
	int sample_size = 0;
	int i = 0;

	if(argc != 2){
		printf("Usage: ./codec 32");
	} else {		
		sample_size = atoi(argv[1]);
		
		sample_data = (char*) malloc (sizeof(char)*sample_size);
		encoded_data = (char*) malloc (sizeof(char)*sample_size);
		decoded_data = (char*) malloc (sizeof(char)*sample_size);		

		/* Generate data */
		printf("Sample data: ");
		for(i=0;i<sample_size;i++){
			sample_data[i] = (char)rand() % 19;
			printf("%c", sample_data[i]+'0');
		}
		printf("\n");

		/* Generate and encode data */
		k = encode(&sample_data[0], &encoded_data[0], sample_size);
		printf("k: %d\n", k);

		/* Display encoded data */
		printf("Encoded data: ");
		for(i=0;i<sample_size;i++){
			printf("%c", encoded_data[i]+'0');
		}
		printf("\n");
				
		/* Decode generated data */
		decode(&decoded_data[0], &encoded_data[0], sample_size, k);

		/* Display decoded data */
		printf("Decoded data: ");
		for(i=0;i<sample_size;i++){
			printf("%c", decoded_data[i]+'0');
		}
		printf("\n");		
				  
		/* Free up used memory */
		free(sample_data);
		free(encoded_data);
		free(decoded_data);
	}
	return 0;
}
