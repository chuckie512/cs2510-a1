// author: Charles Smith <cas275@pitt.edu>

#include <stdio.h>
#include "matrix.h"

int main(){
    int a[10] = {0,5,3,6,7,8,9,4,1,2};
    sort(10, a);

    int i;
    for(i=0; i<10; i++){
        printf("%d ", a[i]);
    }
    printf("\n");

}
