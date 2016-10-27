// author: Charles Smith <cas275@pitt.edu>
// a very simple matrix library
#include <limits.h>
#include <stdint.h>
// a * b = c
void multiply(int32_t n, int32_t m, int32_t l, int32_t a[n][m], int32_t b[m][l], int32_t c[n][l]){
    
    int i = 0;
    int j = 0;
    
    // set result matrix to 0
    for(i=0; i<n; i++){
        for(j=0; j<l; j++){
            c[i][j] = 0;
        }
    }

    // let's multiply!
    // Note: this will take a long time for large matrix
    //       parallelize this for better performance 
    int k =0; 
    for(i=0; i<n; i++){
        for(j=0; j<l; j++){
            for(k=0; k<m; k++){
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
}


//sorts a from smallest to largest
void sort(int32_t n, int32_t a[n]){
    int i;
    int j;
    int swap;
    int done=1;
    
    // bubble sort, for implementation simplicity.
    for(i=0; i<n-1; i++){
        for(j=0; j<n-i-1; j++){
            if(a[j]>a[j+1]){
                swap   = a[j];
                a[j]   = a[j+1];
                a[j+1] = swap;
                done = 0;
            }
        }
        if(done){ // if done == 1 then no swaps occured, we can stop
            break;
        }
        done = 1;
    }
}

int32_t min(int32_t n, int32_t a[n]){
    int i;
    int min = INT_MAX;

    for(i=0; i<n; i++){
        if(a[i]<min){
            min = a[i];
        }
    }

    return min;
}

int32_t max(int32_t n, int32_t a[n]){
    int i;
    int32_t max = INT_MIN;

    for(i=0; i<n; i++){
        if(a[i]>max){
            max = a[i];
        }
    }
    return max;
}
