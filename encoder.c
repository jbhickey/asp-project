#include <stdio.h>
#include <string.h>
#include "encoder.h"
#include "file_io.h"

/* Encodes block data and returns k parameter for block */
int encode(char *e, char *buf, int block_size)
{
	int n = 0;
	int k = 0;
	int z = 0;

	/* Clear buf */
	memset(buf, 0x00, block_size);

	/* Get k parameter */
	k = get_k(get_sse(e, block_size));
	
	for(n=0;n<block_size;n++)
	{
		/* Buffer error and get last k bits */
		buf[n] = e[n];
		buf[n] &= (0xFF >> (8-k));

		/* Buffer error and get last remaining bits */
		z = e[n];
		z &= (0xFF << k);

		/* Prefix sign bit and number of zeroes*/
		buf[n] |= (0x01 << (k+z));
		
		/* Add |1| after kth bit */
		buf[n] |= (0x01 << k);
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
