#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int class_cancelled(int n, int k, int* a) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] <= 0) {
            if (++count == k) {
                return 0;
            }
        }
    }
    return 1;
}


int main() {

    /* Enter your code here. Read input from STDIN. Print output to STDOUT */    
    int t,n,k,a[1000];
    int i = 0;
    scanf("%d", &t);
    fprintf(stderr,"running %d tests\n",t);
    for (i = 0; i < t; i++) {
        fprintf(stderr,"Test %d\n",i);
        scanf("%d", &n);
        scanf("%d", &k);
        fprintf(stderr,"need %d of %d students\n",k,n);
        for (int ai = 0; ai < n; ai++) {
            scanf("%d", &a[ai]);
            fprintf(stderr,"read number: %d\n", a[ai]);
        }
        if (class_cancelled(n,k,&a[0]) == 1) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
    }

    
    return 0;
}

