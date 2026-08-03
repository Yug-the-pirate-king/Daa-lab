#include <cstdio>
#include <cstdlib>

// Represents a single node in a binary tree.
struct Node
{
    int data;
    Node *left;
    Node *right;
};

// Inorder traversal: left subtree, current node, right subtree.
void inorder(Node *root)
{
    if (root == nullptr)
    {
        return;
    }
    inorder(root->left);
    printf("%d -> ", root->data);
    inorder(root->right);
}

// Preorder traversal: current node, left subtree, right subtree.
void preorder(Node *root)
{
    if (root == nullptr)
    {
        return;
    }
    printf("%d -> ", root->data);
    preorder(root->left);
    preorder(root->right);
}

// Postorder traversal: left subtree, right subtree, current node.
void postorder(Node *root)
{
    if (root == nullptr)
    {
        return;
    }
    postorder(root->left);
    postorder(root->right);
    printf("%d -> ", root->data);
}

// Create a new tree node; returns nullptr if allocation fails.
Node *create(int value)
{
    Node *newNode = (Node *)malloc(sizeof(*newNode));
    if (newNode == nullptr)
    {
        // Memory allocation failed; let the caller handle the error.
        return nullptr;
    }

    newNode->data = value;
    newNode->left = nullptr;
    newNode->right = nullptr;
    return newNode;
}

// Recursively free every node in the tree.
void freeTree(Node *root)
{
    if (root == nullptr)
    {
        return;
    }

    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main()
{
    // Build the sample binary tree and validate each allocation.

    Node *root = create(1);
    if (root == nullptr)
    {
        fprintf(stderr, "Error: failed to allocate root node.\n");
        return 1;
    }

    Node *leftChild = create(12);
    if (leftChild == nullptr)
    {
        fprintf(stderr, "Error: failed to allocate left child node.\n");
        freeTree(root);
        return 1;
    }

    Node *rightChild = create(9);
    if (rightChild == nullptr)
    {
        fprintf(stderr, "Error: failed to allocate right child node.\n");
        freeTree(leftChild);
        freeTree(root);
        return 1;
    }

    root->left = leftChild;
    root->right = rightChild;

    Node *leftGrandchild1 = create(5);
    if (leftGrandchild1 == nullptr)
    {
        fprintf(stderr, "Error: failed to allocate left grandchild node.\n");
        freeTree(root);
        return 1;
    }

    Node *leftGrandchild2 = create(6);
    if (leftGrandchild2 == nullptr)
    {
        fprintf(stderr, "Error: failed to allocate left grandchild node.\n");
        freeTree(leftGrandchild1);
        freeTree(root);
        return 1;
    }

    leftChild->left = leftGrandchild1;
    leftChild->right = leftGrandchild2;

    // Ensure the tree is usable before performing traversals.
    if (root == nullptr)
    {
        return 1;
    }

    printf("Inorder: \n");
    inorder(root);
    printf("\n");

    printf("Preorder: \n");
    preorder(root);
    printf("\n");

    printf("Postorder: \n");
    postorder(root);
    printf("\n");

    // Release all dynamically allocated memory.
    freeTree(root);

    return 0;
}