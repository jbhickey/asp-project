#include <stdio.h>
#include <string.h>
#include "prediction.h"


// Take the signal (s) to produce the error for an order
// return order to write to block
// Remember encode error[order] to 
int optimum_predictor(char *signal_data, char *auto_corr_func)
{
	char sse[3] = {0};
	char error[3][] = {0};
	long norm_factor = 0;
	int order = 0;
	int n = 0;
	int i = 0;

	norm_factor = get_norm_factor(&signal_data[0]);	

	auto_corr(&signal_data[0], &auto_corr_func[0], norm_factor);	
   
	for(n=0;n<3;n++)
	{
		// Get coeffs for current order
		get_coeffs(&coeffs[0], &auto_corr_func[0], n);

		// Calculate error vector
		
		// Calculate SSE for order
		for(i=0;i<sizeof(error[n]);i++)
			sse[n] += error[n][i];
		
		sse[n] /= sizeof(error[n]);
	}

	// Compare errors from different order predictors
	for(i=1;i<3;i++)
	{
		if(sse[i]<sse[i-1])
			order = i;
		else
			order = 0;
	}
	
	// Encode using error[order]	
	return order;	
}

// Take signal (s) and produce normalized auto-correlation function (r) 
// given normalization factor (norm_factor)
void auto_corr(char *s, char *r, long norm_factor)
{
	// TODO: auto-correlation
	
	// Normalise each element 
	for(i=0;i<sizeof(r);i++)
		r[i] /= norm_factor;
}

// Return normalization actor given signal (s)
long get_norm_factor(char *s)
{
	long f = 0; // normalisation factor

	// Iterate through signal and square each element
	for(i=0;i<sizeof(s);i++)
		f += s[i]*s[i];
	
	return f;			
}

// Take auto-correlation function (r) and return k amount of coeffs (a) 
// given order (n)
void get_coeffs(int *a, char *r, int n)
{
	//a[k];

}
