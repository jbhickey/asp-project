#include <stdio.h>
#include <string.h>
#include "encoder.h"
#include "file_io.h"

/* Rice coding for a k = 2 parameter, takes error vector 
   and for each index performs rice coding */
void encode(char *e, char *buf)
{
	int n = 0;
	
	for(n=0;n<BLOCK_SIZE;n++)
	{
		// Get last k bits
		buf[n] += e[n] && 0x03;

		// No of zeroes = Remaining 6-bits
		z += e[n] && 0xFC;

		// Prefix sign-bit and z zeros
		buf[n] += 1 << (2+z);		
	}
}

int get_k(int s_error)
{
	int k = 0;
	
	// Source: Dennis Deng, assignment sheet
	for(k = 7;k >= 1;k--)
	{
		if(((s_error >> k) & 1) == 1)
			break;
	}        
	
	return k;
}
