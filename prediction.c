#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "prediction.h"
#include "file_io.h"

/* Average 1st order linear predictor, take signal data and return
   eq e[n] = s[n] - sp[n]
   sp[n] = 0.5s[n-1] + 0.5s[n-2] */
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
