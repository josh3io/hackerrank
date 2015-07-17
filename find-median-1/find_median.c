#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
int
find_min(int a, int b, int c) {
    if (a < b && a < c) return a;
    if (b < a && b < c) return b;
    return c;
}

void
min_heapdown(int *a,int len,int pos) {
    int left,right,nextpos,tmp;
    left = 2*pos+1;
    right = 2*pos+2;
    if (right >= len) {
        if (left >= len) {
            return;
        } else {
            nextpos = left;
        }
    } else {
        if (a[left] <= a[right]) {
            nextpos = left;
        } else {
            nextpos = right;
        }
    }
    if (a[pos] > a[nextpos]) {
        tmp = a[nextpos];
        a[nextpos] = a[pos];
        a[pos] = tmp;
        min_heapdown(a,len,nextpos);
    }
}



void
min_heapify(int *a,int pos) {
    int tmp,parent_pos;

    if (pos == 0) return;

    // get parent
    parent_pos = pos % 2 == 0 ? (pos-2)/2 : (pos-1)/2;

    // swap and go up if parent < child
    if (a[parent_pos] > a[pos]) {
        tmp = a[pos];
        a[pos] = a[parent_pos];
        a[parent_pos] = tmp;
        min_heapify(a,parent_pos);
    }
}

void
min_insert(int tmp, int *a, int len) {
    a[len] = tmp;
    //printf("%d is %d\n",len,a[len]);
    min_heapify(a,len);
}


int
find_max(int a, int b, int c) {
    if (a > b && a > c) return a;
    if (b > a && b > c) return b;
    return c;
}


void
max_heapdown(int *a,int len,int pos) {
    int left,right,nextpos,tmp;
    left = 2*pos+1;
    right = 2*pos+2;
    //printf("%d left %d right %d\n",len,left,right);
    if (right >= len) {
        if (left >= len) {
            //printf("left <= len\n");
            return;
        } else {
            nextpos = left;
        }
    } else {
        if (a[left] >= a[right]) {
            nextpos = left;
        } else {
            nextpos = right;
        }
    }
    //printf("maxdown %d vs %d %d < %d; ",pos,nextpos,a[pos],a[nextpos]);
    if (a[pos] < a[nextpos]) {
        tmp = a[nextpos];
        a[nextpos] = a[pos];
        a[pos] = tmp;
        //printf("swap\n");
        max_heapdown(a,len,nextpos);
    }
    //printf("\n");
}


void
max_heapify(int *a,int pos) {
    int tmp,parent_pos;

    if (pos == 0) return;

    // get parent
    parent_pos = pos % 2 == 0 ? (pos-2)/2 : (pos-1)/2;

    //printf("comp %d %d (%d < %d)",parent_pos,pos,a[parent_pos],a[pos]);
    // swap and go up if parent < child
    if (a[parent_pos] < a[pos]) {
        tmp = a[pos];
        a[pos] = a[parent_pos];
        a[parent_pos] = tmp;
        max_heapify(a,parent_pos);
    }
    //printf("\n");
}

void
max_insert(int tmp, int *a, int len) {
    a[len] = tmp;
    //printf("%d is %d\n",len,a[len]);
    max_heapify(a,len);
}


void
print_heap(char *t, int *a,int len) {
    int i;
    //printf("printing %s heap: ",t);
    for (i=0;i<len;i++) {
        //printf("%d, ",a[i]);
    }
    //printf("\n");
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */    
    
    int i,n,tmp,*max_heap,*min_heap,max_size=0,min_size=0;

    scanf("%d",&n);
    max_heap = malloc(sizeof(int) * n);
    min_heap = malloc(sizeof(int) * n);

    for (i=0;i<n;i++) {
        scanf("%d",&tmp);
        if (tmp < min_heap[0]) {
            //printf("max insert %d\n",tmp);
            max_insert(tmp,max_heap,max_size++);
        } else {
            //printf("min insert %d\n",tmp);
            min_insert(tmp,min_heap,min_size++);
        }

        //print_heap("max",max_heap,max_size);
        //print_heap("min",min_heap,min_size);

        if (i % 2 == 1) {
            if (min_size > max_size) {
                // swap min root to max heap
                //printf("move %d from min to max\n",min_heap[0]);
                tmp = min_heap[0];
                min_heap[0] = min_heap[min_size-1];
                min_heapdown(min_heap,--min_size,0);
                max_insert(tmp,max_heap,max_size++);
            } else if (max_size > min_size) {
                // swap max root to min heap
                //printf("move %d from max to min\n",max_heap[0]);
                tmp = max_heap[0];
                max_heap[0] = max_heap[max_size-1];
                max_heapdown(max_heap,--max_size,0);
                min_insert(tmp,min_heap,min_size++);
            }
        }

        print_heap("max",max_heap,max_size);
        print_heap("min",min_heap,min_size);

        if (i % 2 == 1) {
            // median is mean of min and max 0th elements
            printf("%.1f\n",(double)(min_heap[0]+max_heap[0])/2);
        } else {
            // median is 0th of largest heap
            if (max_size > min_size) {
                printf("%.1f\n",(double)max_heap[0]);
            } else {
                printf("%.1f\n",(double)min_heap[0]);
            }
        }
    }

    free(max_heap);
    free(min_heap);

    return 0;
}

