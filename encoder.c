#include <stdio.h>
#include <string.h>
#include "encoder.h"
#include "file_io.h"

/* Rice coding for a k = 2 parameter, takes error vector 
   and for each index performs rice coding */
void encode(char *e, char *buf, int block_size)
{
	int n = 0;
	int z = 0;
	int k = 0;

	/* Get k parameter */
	k = get_k(get_sse(e));
	
	for(n=0,z=0;n<block_size;n++)
	{
		/* Get last k bits */
		buf[n] = e[n] && (0xFF >> (8-k));

		/* No of zeroes = Remaining 6-bits */
		z = e[n] && (0xFF << k);
		
		/* Prefix sign-bit and z zeros */
		buf[n] |= 1 << (2+z);		
	}
}

int get_sse(char *e)
{
	int sse = 0;
	int se = 0;
	int i = 0;

	for(i=0;i<strlen(e);i++)
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
