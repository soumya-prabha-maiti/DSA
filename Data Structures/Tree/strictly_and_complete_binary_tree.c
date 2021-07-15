// C program to check whether a given Binary Tree is Strictly binary and Complete or not
#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0

/* Tree node structure */
struct Node
{
    int data;
    struct Node *left, *right;
};

struct Node *createNode(int data);
int leafLevel(struct Node *node);
int isStrictlyBinary(struct Node *node);
int isComplete(struct Node *node);
int isCompleteRecursive(struct Node *node, int d, int level);
void inorder(struct Node *node);

int main()
{
    struct Node *root = NULL;


    // The tree is changed by changing this part of the code
    root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    root->left->left = createNode(4);
    root->left->right = createNode(5);
    root->right->left = createNode(6);
    root->right->right = createNode(7);

    
    printf("\n\t***BINARY TREE***\n");
    printf("\nNote : For inorder traversal (( 2 ) 1 ( 3 )) represents a tree with 1 as the root, 2 as the left child of 1, and 3 as the right child of 1.\n");
    printf("\nInorder traversal of the given binary tree:\n");
    inorder(root);

    printf("\n\nStrictly binary tree : ");
    if (isStrictlyBinary(root))
        printf("Yes");
    else
        printf("No");

    printf("\nComplete binary tree : ");
    if (isComplete(root))
        printf("Yes");
    else
        printf("No");

    return 0;
}


//Function that allocates a new node with the given data and NULL left and right pointers.
struct Node *createNode(int data)
{
    struct Node *node = (struct Node *)malloc(sizeof(struct Node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}


// Returns level of leftmost leaf.
int leafLevel(struct Node *node)
{
    int d = 0;
    while (node != NULL)
    {
        d++;
        node = node->left;
    }
    return d;
}

// Function to check if a binary tree is a strictly binary tree. 
int isStrictlyBinary(struct Node *node)
{
	// If empty tree
	if (node == NULL)
		return TRUE;

	// If leaf node
	if (node->left == NULL && node->right == NULL)
		return TRUE;

	// If both left and right are not NULL, then check whether both left & right subtrees are strictly binary
	if ((node->left) && (node->right))
		return (isStrictlyBinary(node->left) && isStrictlyBinary(node->right));

	//If all the above conditions are false
	return FALSE;
}

// Function to check if a binary tree is Complete or not
int isCompleteRecursive(struct Node *node, int d, int level)
{
    // An empty tree is Complete
    if (node == NULL)
        return TRUE;

    // If leaf node, then its depth must be same as
    // depth of all other leaves.
    if (node->left == NULL && node->right == NULL)
        return (d == level + 1);

    // If internal node and one child is empty
    if (node->left == NULL || node->right == NULL)
        return FALSE;

    // Left and right subtrees must be Complete.
    return isCompleteRecursive(node->left, d, level + 1) && isCompleteRecursive(node->right, d, level + 1);
}


// Wrapper over isCompleteRecursive()
int isComplete(struct Node *node)
{
    int d = leafLevel(node);
    return isCompleteRecursive(node, d, 0);
}

// Function to do inorder traversal of BST
void inorder(struct Node *node)
{
    if (node != NULL)
    {
        printf("(");
        inorder(node->left);
        printf(" %d ", node->data);
        inorder(node->right);
        printf(")");
    }
}