#ifndef PREDICT_H
#define PREDICT_H

void avg_predictor(char *s, char *e, int block_size);
void n_order_predictor(char *s, char *e, int block_size, int n_order);

#endif
