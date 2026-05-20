#include <stdio.h>
#include <stdlib.h>

struct node
{
    int item;
    struct node *left, *right;
};

void inorder(struct node *r)
{
    if (!r)
        return;
    inorder(r->left);
    printf("%d -> ", r->item);
    inorder(r->right);
}

void preorder(struct node *r)
{
    if (!r)
        return;
    printf("%d -> ", r->item);
    preorder(r->left);
    preorder(r->right);
}

void postorder(struct node *r)
{
    if (!r)
        return;
    postorder(r->left);
    postorder(r->right);
    printf("%d -> ", r->item);
}

struct node *create(int val)
{
    struct node *n = (struct node *)malloc(sizeof(struct node));
    n->item = val;
    n->left = n->right = NULL;
    return n;
}

int main()
{
    // Using create() to map out our tree cleanly
    struct node *root = create(1);
    root->left = create(12);
    root->right = create(9);
    root->left->left = create(5);
    root->left->right = create(6);

    printf("Inorder: \n");
    inorder(root);
    printf("\n");

    printf("Preorder: \n");
    preorder(root);
    printf("\n");

    printf("Postorder: \n");
    postorder(root);
    printf("\n");

    return 0;
}