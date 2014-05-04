#ifndef PREDICT_H
#define PREDICT_H

int optimum_predictor(void);
void auto_corr(char *s, char *r, long norm_factor);
long get_norm_factor(char *s);
void get_coeffs(int *a, char *r, int n);

#endif
