#include <stdio.h>
#include <string.h>
#include "decoder.h"

/* Decode an error vector for each sample in encoded block */
void decode(char *e, char *buf, int block_size, int k)
{
	int n = 0;
	unsigned char z = 0;
	unsigned char tmp = 0;
	unsigned char bit_mask = 0;
	int cnt = 0;
	
	/* Clear error */
	memset(e, 0x00, block_size);

	for(n=0;n<block_size;n++)
	{			
		/* Buffer encoded data */
		tmp = buf[n];

		/* Buffer encoded data and affix last k bits */
		bit_mask = 0xFF >> (8-k);
		e[n] = tmp;
		e[n] &= bit_mask;
		
		/* Count how many zeroes occur */		
		while((tmp & (0x02 << (k+cnt))) == 0){
			cnt++;
			z++;	
		}
		
		/* Shift z to kth bit */
		z <<= k;
		
		/* Affix z */
		e[n] |= z;

		/* Reset parameters for next sample */
		z = 0;
		cnt = 0;
	}
}

/* Simply returns top three bits of first byte in current block */
int get_encoded_k(char *buf)
{
	return (int)buf[0];
}
