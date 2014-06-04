#include <stdio.h>
#include <string.h>
#include "decoder.h"

/* Decode an error vector for each sample in encoded block */
void decode(int *input_data, int *output_data, int size, int k)
{
	int n = 0;
	int z = 0;
	int bit_mask = 0;

	/* Clear error */
	memset(output_data, 0x00, size);

	for(n=0;n<size;n++)
	{
		/* Buffer encoded data and affix last k bits */
		bit_mask = 0xFF >> (8-k);
		output_data[n] = input_data[n];
		output_data[n] &= bit_mask;

		/* Count how many zeroes occur */
		bit_mask = 0x02 << k;
		while((input_data[n] & bit_mask) == 0){
			bit_mask <<= 1;
			z++;
		}

		/* Shift z to kth bit */
		z <<= k;

		/* Affix z */
		output_data[n] |= z;

		/* Reset parameters for next sample */
		z = 0;
	}
}

