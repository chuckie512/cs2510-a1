// author: Charles Smith <cas275@pitt.edu>
// The code for these functions are implemented in matrix.c
//
// For the RPC project, do not compile the client with matrix.c, 
// instead use the client stub

#ifndef MATRIX_H
#define MATRIX_H

void multiply(int n, int m, int l, int a[n][m], int b[m][l], int c[n][l]);
void sort(int n, int a[n]);
int min(int n, int a[n]);
int max(int n, int a[n]);

#endif
