#include <stdio.h>
#include <string.h>
#include "decoder.h"

/* Decode an error vector for each sample in encoded block */
void decode(char *e, char *buf, int block_size, int k)
{
	int n = 0;
	int z = 0;

	/* Clear error */
	memset(e, 0x00, block_size);

	for(n=0,z=k;n<block_size;n++)
	{				
		/* Buffer encoded data and affix last k bits */
		e[n] = buf[n];
		e[n] &= (0xFF >> (8-k));
		
		/* Count number of zeroes starting from kth bit */
		while ((buf[z] && 0xFF) == 0)
			z++;
		
		/* Remove k count from z */
		z -= k+1;

		/* Affix number starting after k bits */
		e[n] |= (z << (k+1));
	}
}

/* Simply returns top byte of current block */
int get_encoded_k(char *buf)
{
	return (int)buf[0];
}
