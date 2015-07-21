#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

void print_inorder(int tree[], int idx, int size) {
    if (2*idx+1 <= size) {
        print_inorder(tree,2*idx+1,size);
    }
    printf("%d ",tree[idx]);
    if (2*idx+2 <= size) {
        print_inorder(tree,2*idx+2,size);
    }
}

int parent(int idx) {
    if (idx % 2 == 0) {
        return (idx-2)/2;
    } else {
        return (idx-1)/2;
    }
}

int lca(int tree[], int v1, int v2, int size) {
    int idx1,idx2;
    int thelca;
    idx1=size-1;
    idx2=size-1;
    while (tree[idx1] != v1 || tree[idx2] != v2) {
        if (tree[idx1] != v1) {
            --idx1;
        } 
        if (tree[idx2] != v2) {
            --idx2;
        }
    }
    while (tree[idx1] != tree[idx2]) {
        if (idx1 > idx2) {
            idx1 = parent(idx1);
        } else if (idx2 > idx1) {
            idx2 = parent(idx2);
        } else {
            idx1 = parent(idx1);
            idx2 = parent(idx2);
        }
    }
    return tree[idx1];
}



int main() {
    int v1,v2,i;

    int tree[6] = {4,2,7,1,3,6};

    for (i=0;i<6;i++) {
        printf("%d ",tree[i]);
    }
    printf("\n");
    print_inorder(tree,0,6);
    printf("\npick two nodes to find their LCA: ");

    scanf("%d",&v1);
    scanf("%d",&v2);


    int thelca = lca(tree,v1,v2,6);

    printf("lca %d\n",thelca);

    return 0;
}

