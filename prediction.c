#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "prediction.h"
#include "file_io.h"

void avg_predictor(char *s, char *e, int block_size)
{
	char *sp = (char*) malloc (sizeof(char)*block_size);
	int n = 0;

	// Iterate through signal and calculate prediction 
	for(n=0;n<block_size;n++)
	{
		if(n==0)
			sp[n] = s[n];
		else if(n==1)
			sp[n] = (s[n-1]/2);
		else if(n>=2)
			sp[n] = ((s[n-1]/2) + (s[n-2]/2));
		
		// Assign error for sample
		e[n] = s[n] - sp[n];		
	}
	free(sp);
}

void n_order_predictor(char *s, char *e, int block_size, int n_order)
{
	char *sp = (char*) malloc (sizeof(char)*block_size);
	int n = 0;

	/* Prediction */
	switch(n_order){		
	case 1:
		for(n=0;n<block_size;n++){
			sp[n] = s[n-1];
		}
		break;
	case 2:
		for(n=0;n<block_size;n++){
			sp[n] = 2*s[n-1];
			sp[n] -= s[n-2];
		}
		break;
	case 3:
		for(n=0;n<block_size;n++){
			sp[n] = 3*s[n-1];
			sp[n] -= 3*s[n-2];
			sp[n] += s[n-3];
		}
		break;
	default:
		avg_predictor(s, e, block_size);
		break;
	}

	/* Calculate error for each sample */
	for(n=0;n<block_size;n++){
		e[n] = sp[n] - s[n];
	}
}
