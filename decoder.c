#include <stdio.h>
#include <string.h>
#include "decoder.h"

/* Decode an error vector for each sample in encoded block */
void decode(char *e, char *buf, int block_size, int k)
{
	
}

/* Simply returns top three bits of first byte in current block */
int get_encoded_k(char *buf)
{
	return (int)(buf[0] && 0xE0);
}
