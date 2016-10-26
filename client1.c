// author: Charles Smith
//
// a simple test client for the matrix library

#include "matrix.h"
#include <stdio.h>

int main(){

    // create matrix
    int a[3][4] = {
        {1,2,3,4},
        {4,3,2,1},
        {1,1,1,1}
    };
    int b[4][3] = {
        {2,2,4},
        {4,5,6},
        {7,8,9},
        {1,5,5}
    };
    int c[3][3];

    multiply(3, 4, 3, a, b, c);

    int i;
    int j;
    for(i=0; i<3; i++){
        for(j=0; j<3; j++){
            printf("%d ", c[i][j]);
        }
        printf("\n");
    }
}
