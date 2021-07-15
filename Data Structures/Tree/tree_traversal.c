// C program for different tree traversals
#include <stdio.h>
#include <stdlib.h>

// Tree node structure
struct Node
{
    int data;
    struct Node *left;
    struct Node *right;
};

struct Node *createNode(int data);
void preorder(struct Node *node);
void inorder(struct Node *node);
void postorder(struct Node *node);

int main()
{
    struct Node *root;

    // The tree is changed by changing this part of the code
    // root = createNode(1);
    // root->left = createNode(2);
    // root->right = createNode(3);
    // root->left->left = createNode(4);
    // root->left->right = createNode(5);
    // root->right->left = createNode(6);

    root = createNode(6);
    root->right = createNode(7);
    root->right->left = createNode(4);
    root->right->right = createNode(8);

    printf("\n\t***BINARY TREE : TRAVERSAL***\n");
    printf("\n\nPre-order traversal :\n");
    preorder(root);

    printf("\n\nIn-order traversal :\n");
    inorder(root);

    printf("\n\nPost-order traversal :\n");
    postorder(root);

    return 0;
}

//Function that allocates a new node with the given data and NULL left and right pointers.
struct Node *createNode(int data)
{
    struct Node *node = (struct Node *)malloc(sizeof(struct Node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return (node);
}

// Print the nodes of a binary tree according to preorder traversal.
void preorder(struct Node *node)
{
    if (node != NULL)
    {
        printf("(");

        /* first print the data of node */
        printf(" %d ", node->data);

        /* then recur on left sutree */
        preorder(node->left);

        /* now recur on right subtree */
        preorder(node->right);

        printf(")");
    }
}

// Print the nodes of a binary tree according to inorder traversal.
void inorder(struct Node *node)
{
    if (node != NULL)
    {
        printf("(");

        /* first recur on left child */
        inorder(node->left);

        /* then print the data of node */
        printf(" %d ", node->data);

        /* now recur on right child */
        inorder(node->right);

        printf(")");
    }
}

// Print the nodes of a binary tree according to postorder traversal.
void postorder(struct Node *node)
{
    if (node != NULL)
    {
        printf("(");

        // first recur on left subtree
        postorder(node->left);

        // then recur on right subtree
        postorder(node->right);

        // now print the data of the node
        printf(" %d ", node->data);

        printf(")");
    }
}