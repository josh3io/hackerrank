#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

typedef int bool;
#define true 1
#define false 0

typedef struct station {
    int petrol;
    int dist;
} station_t;

bool 
check_path(station_t *s,int start,int n) {
    int fuel = 0;
    int i = start;
    //fprintf(stderr,"check path starting at %d: ",start);
    while (i < n) {
        //printf("station %d has %d petrol and %d to next\n",i,s[i].petrol,s[i].dist);
        fuel += s[i].petrol;
        fuel -= s[i].dist;

        //printf("fuel level when arriving at next station is %d\n",fuel);

        if (fuel < 0) {
            //printf("out of fuel %d\n",fuel);
            return false;
        }
        i++;
        if (start > 0) {
            if (i == start) {
                //fprintf(stderr,"success %d\n",fuel);
                return true;
            } else if (i == n) {
                i = 0;
            }
        }
    }
    //fprintf(stderr,"success %d\n",fuel);
    return true;
}

int main() {

    /* Enter your code here. Read input from STDIN. Print output to STDOUT */    

    int n,i,rot=-1;
    station_t *s;
    scanf("%d",&n);

    s = malloc(n * sizeof(station_t));
    if (NULL == s) {
        fprintf(stderr,"malloc failed\n");
        return(-1);
    }

    for (i=0;i<n;i++) {
        scanf("%d",&s[i].petrol);
        scanf("%d",&s[i].dist);
    }


    while (++rot < n) {
        if (check_path(s,rot,n)) {
            break;
        }

    }

    printf("%d\n",rot);
    

    free(s);

    return 0;
}

