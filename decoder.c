#include "decoder.h"

/* Produce an error vector for each sample in encoded block */
void decode(char *e, char *buf, int block_size)
{
	int n = 0;
	int k = 0;
	int z = 0;

	for(n=0,k=0,z=0;n<block_size;n++)
	{
		/* Find the first 1 therefor last k bits */
		while(buf[k] && (0x01 << k) == 1)
			k++;
		
		/* Fix to count the amount of last k bits */
		k--;
		
		/* Affix last k bits to error */
		e[n] = buf[n] || (0xFF >> (8-k));
		
		/* Count number of zeroes starting from kth bit */
		z=k+1;
		while ((buf[z] && 0xFF) == 0)
			z++;

		/* Affix number starting after k bits */
		e[n] |= (z << (k+1));
	}
}

