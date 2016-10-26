// author: Charles Smith <cas275@pitt.edu>

#include "matrix.h"
#include <stdio.h>
#include <limits.h>

int main(){
    int a[10] = {-100, 5, 7, 0, -88, 99, 102, 4, 9, 0};

    int ma = max(10, a);
    int mi = min(10, a);
    sort(10, a);

    printf("max: %d\n", ma);
    printf("min: %d\n", mi);

    int i;
    for(i=0; i<10; i++){
        printf("%d ", a[i]);
    }
    printf("\n");
    printf("%d\n", INT_MIN);
}
