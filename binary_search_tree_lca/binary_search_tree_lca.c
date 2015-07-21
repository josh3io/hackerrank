#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>


typedef struct node
{
   int data;
   struct node * left;
   struct node * right;
} node;
typedef struct node_path
{
    node * thenode;
    struct node_path * parent;
} node_path;
typedef struct stack
{
    int size;
    node_path * top;
} stack;
void path_to(node * root, int val, stack * path)
{
    node_path * temp;
    if (path->top != NULL && path->top->thenode->data == val) {
        printf("done\n");
        return;
    }
    temp = (node_path *)malloc(sizeof(node_path));
    temp->thenode = root;
    temp->parent = path->top;
    path->top = temp;
    path->size ++;

    if (root->data == val) {
        //printf("found it! %d, %d\n",root->data,path->top->thenode->data);
        return;
    }

    //printf("end of list is now %d\n",path->top->thenode->data);
    if (root->left != NULL) {
        //printf("go left\n");
        path_to(root->left,val,path);
    }
    //printf("check after left %d, %d\n",root->data,path->top->thenode->data);
    if (path->top->thenode->data == val) {
        //printf("return from left\n");
        return;
    }
    if (root->right != NULL) {
        //printf("go right\n");
        path_to(root->right,val,path);
    }
    //printf("check after right %d, %d\n",root->data,path->top->thenode->data);
    if (path->top->thenode->data == val) {
        return;
    }
    if (path->top != NULL) {
        temp = path->top;
        path->top = temp->parent;
        path->size --;
        //printf("free %d from right\n",temp->thenode->data);
        free(temp);
    }
}

node * lca(node * root, int v1,int v2)
{
    stack *path1,*path2;
    node_path *temp1,*temp2;
    int count1,count2;
    path1 = (stack *)malloc(sizeof(stack));
    path2 = (stack *)malloc(sizeof(stack));
    path1->top = NULL;
    path1->size = 0;
    path2->top = NULL;
    path2->size = 0;
    path_to(root,v1,path1);
    path_to(root,v2,path2);

    temp1 = path1->top;
    count1 = path1->size;
    temp2 = path2->top;
    count2 = path2->size;
    while (temp1 != NULL && temp2 != NULL) {
        if (temp1->thenode->data != temp2->thenode->data) {
            if (count1 > count2) {
                temp1 = temp1->parent;
                --count1;
            } else if (count2 > count1) {
                temp2 = temp2->parent;
                --count2;
            } else {
                temp1 = temp1->parent;
                temp2 = temp2->parent;
                --count1;
                --count2;
            }
        } else {
            free(path1);
            free(path2);
            return temp1->thenode;
        }
    }  
    return NULL;
}



void
print_insert_order(node * root) {
    if (root->left != NULL) {
        print_insert_order(root->left);
    }
    printf("%d ",root->data);
    if (root->right != NULL) {
        print_insert_order(root->right);
    }
}

void 
init(node * root) {
    root->data = 4;
    root->left = (node *)malloc(sizeof(node));
    root->right = (node *)malloc(sizeof(node));
    root->left->data = 2;
    root->right->data = 7;
    root->left->left = (node *)malloc(sizeof(node));
    root->left->right = (node *)malloc(sizeof(node));
    root->left->left->data = 1;
    root->left->right->data = 3;
    root->right->left = (node *)malloc(sizeof(node));
    root->right->left->data = 6;
}

int main() {
    node * root = (node *)malloc(sizeof(node));
    int v1,v2;
    init(root);

    print_insert_order(root);
    printf("pick two nodes to find their LCA: ");

    scanf("%d",&v1);
    scanf("%d",&v2);


    node * thelca = lca(root,v1,v2);

    printf("lca %d\n",thelca->data);

}
