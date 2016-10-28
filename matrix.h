// author: Charles Smith <cas275@pitt.edu>
// The code for these functions are implemented in matrix.c
//
// For the RPC project, do not compile the client with matrix.c, 
// instead use the client stub

#ifndef MATRIX_H
#define MATRIX_H
#include <stdint.h>

void multiply(int32_t n, int32_t m, int32_t l, int32_t a[n][m], int32_t b[m][l], int32_t c[n][l]);
void sort(int32_t n, int32_t a[n]);
int32_t min(int32_t n, int32_t a[n]);
int32_t max(int32_t n, int32_t a[n]);

#endif
