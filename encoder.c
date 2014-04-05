#include <stdio.h>
#include <string.h>

#include "encoder.h"

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
