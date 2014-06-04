#include <stdio.h>
#include <string.h>
#include "encoder.h"
#include "file_io.h"

/* Encodes block data and returns k parameter for block */
int encode(char *input_data, int *output_data, int size)
{
	int n = 0;
	int k = 0;
	int z = 0;
	int bit_mask = 0;
	char num_bits = 0;

	/* Clear buf */
	memset(output_data, 0x00, size);

	/* Get k parameter given average sum squared error (input_data) */
	k = get_k(get_sse(input_data, size)/size);
	write_byte((char)k, "Output/compressed.out");

	for(n=0;n<size;n++)
	{
		/* Get last k bits */
		bit_mask = 0xFF >> (8-k);
		output_data[n] = (int)input_data[n];
		output_data[n] &= bit_mask;

		/* Add |1| after kth bit  */
		output_data[n] |= (0x01 << k);

		/* Buffer error and get last Z remaining bits */
		bit_mask = 0xFF << k;
		z = (int)input_data[n];
		z &= bit_mask;

		/* Align Z with bit 0 */
		z >>= k;

		/* How many bits to write */
		num_bits = k+1+z+1;

		/* Prefix sign bit and Z amount of zeroes */
		output_data[n] |= (0x02 << (k+z));
		
		/* Start putting bits from sign bit */
		bit_mask = 0x01 << (num_bits-1);

		/* Code generated, write out */
		while(num_bits > 0){
			put_bit(output_data[n] & bit_mask);
			bit_mask >>= 1;
			num_bits--;
		}
	}
	return k;
}

/* Given an error vector */
/* returns the sum of squared error */
int get_sse(char *e, int block_size)
{
	int sse = 0;
	int se = 0;
	int i = 0;

	for(i=0;i<block_size;i++)
	{
		se = e[i]*e[i];
		sse += se;
	}

	return sse;
}

int get_k(int s_error)
{
	int k = 0;

	/* Source: Dennis Deng, assignment sheet */
	for(k = 7;k >= 1;k--)
	{
		if(((s_error >> k) & 1) == 1)
			break;
	}

	return k;
}

