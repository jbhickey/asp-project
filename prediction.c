#include <stdio.h>
#include <string.h>
#include "prediction.h"
#include "file_io.h"

/* Average 1st order linear predictor, take signal data and return
   eq e[n] = s[n] - sp[n]
   sp[n] = 0.5s[n-1] + 0.5s[n-2] */
void avg_predictor(char *s, char *e)
{
	char sp[BLOCK_SIZE] = {0};

	// Iterate through signal and calculate prediction 
	for(n=0;n<BLOCK_SIZE;n++)
	{
		if(n)
			sp[n] = s[n-1] >> 1;
		else
			sp[n] = s[n];
		
		// Assign error for sample
		e[n] = s[n] - sp[n];		
	}
}

/* Take the signal (s) to produce the error for an order
   return order with smallest error to write to block
   Remember encode error[order] to */
int optimum_predictor(char *signal_data, char *auto_corr_func, char *error)
{
	char sse[3] = {0};
	int coeffs[3];
	long norm_factor = 0;
	int order = 0;
	int n = 0;
	int i = 0;

	// Get normalisation factor for a given signal block
	norm_factor = get_norm_factor(signal_data);	

	// Generate normalised auto-correlation function
	auto_corr(signal_data, &auto_corr_func[0], norm_factor);	
   
	for(n=0;n<3;n++)
	{
		// Get coeffs for current order
		get_coeffs(&coeffs[0], &auto_corr_func[0], n);

		// Calculate error vector given coeffs and signal data
		// error_vect(&coeffs[0], signal_data, error);

		// Calculate SSE for order
		for(i=0;i<sizeof(error[n]);i++)
			sse[n] += error[n][i];
		
		sse[n] /= strlen(error[n]);
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

// Return normalization factor given signal (s)
long get_norm_factor(char *s)
{
	long f = 0; // normalisation factor

	// Iterate through signal and square each element
	for(i=0;i<strlen(s);i++)
		f += s[i]*s[i];
	
	return f;			
}

// Take auto-correlation function (r) and return k amount of coeffs (a) 
// given order (n)
void get_coeffs(int *a, char *r, int n)
{
	//a[k];

}
