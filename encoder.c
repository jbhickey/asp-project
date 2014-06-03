#include <stdio.h>
#include <string.h>
#include "encoder.h"

/* Encodes block data and returns k parameter for block */
int encode(char *e, char *buf, int block_size)
{
	int n = 0;
	int k = 0;
	unsigned char z = 0;
	unsigned char tmp = 0;
	unsigned char bit_mask = 0;

	/* Clear buf */
	memset(buf, 0x00, block_size);

	/* Get k parameter given average sum squared error */
	k = get_k(get_sse(e, block_size)/block_size);
	
	for(n=0;n<block_size;n++)
	{
		/* Buffer error */
		tmp = e[n]; 

		/* Get last k bits */
		bit_mask = 0xFF >> (8-k);
		buf[n] = tmp;
		buf[n] &= bit_mask;

		/* Add |1| after kth bit  */
		buf[n] |= (0x01 << k);

		/* Buffer error and get last remaining bits */
		bit_mask = 0xFF << k;
		z = tmp;
		z &= bit_mask;		

		/* Prefix sign bit and number of zeroes*/
		if(tmp > 0){
			buf[n] |= (0x02 << (k+z));
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
