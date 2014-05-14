#ifndef PREDICT_H
#define PREDICT_H

void avg_predictor(char *s, char *e);
int optimum_predictor(char *signal_data, char *auto_corr_func, char *error);
void auto_corr(char *s, char *r, long norm_factor);
long get_norm_factor(char *s);
void get_coeffs(int *a, char *r, int n);

#endif
