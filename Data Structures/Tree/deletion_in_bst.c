// C program to demonstrate delete operation in binary search tree
#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node *left, *right;
};

struct Node *createNode(int data);
void inorder(struct Node *node);
struct Node *insert(struct Node *node, int data);
struct Node *search(struct Node *node, int search);
struct Node *minValueNode(struct Node *node);
struct Node *delete (struct Node *node, int value);

int main()
{
    struct Node *root = NULL, *ptr;
    int choice, data;
    printf("\nNote :In this program ,for inorder traversal (( 1 ) 2 ( 3 )) represents a tree with 2 as the root, 1 as the left child of 2, and 3 as the right child of 2.\n");

    while (1)
    {
        printf("\n\n\t***BINARY SEARCH TREE***\n");
        printf("\n1.Insert new element");
        printf("\n2.Search for an element");
        printf("\n3.Delete an element");
        printf("\n4.Display");
        printf("\n0.Exit");

        printf("\n\nEnter your choice : ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter data to insert(integer):");
            scanf("%d", &data);
            root = insert(root, data);

            printf("Inorder traversal of the tree after this operation:\n");
            inorder(root);
            break;

        case 2:
            printf("Enter data to search(integer):");
            scanf("%d", &data);
            ptr = search(root, data);
            if (ptr == NULL)
                printf("\n%d not found in the tree\n", data);
            else
                printf("\n%d found in the tree\n", data);

            printf("Inorder traversal of the tree after this operation:\n");
            inorder(root);
            break;

        case 3:
            printf("Enter data to delete(integer):");
            scanf("%d", &data);
            root = delete (root, data);

            printf("Inorder traversal of the tree after this operation:\n");
            inorder(root);
            break;

        case 4:
            printf("Inorder traversal of the tree :\n");
            inorder(root);
            break;

        case 0:
            exit(0);

        default:
            printf("\nInvalid Input");
            break;
        }
    }
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

// Function to insert a new node with given key in BST
struct Node *insert(struct Node *node, int data)
{
    // If the tree is empty, return a new node
    if (node == NULL)
        return createNode(data);

    // Otherwise, recur down the tree to find the appropriate plate to insert the new element
    if (data < node->data)
        node->left = insert(node->left, data);
    else
        node->right = insert(node->right, data);

    // return the (unchanged) node pointer
    return node;
}

/* Given a non-empty binary search tree, return the node with minimum key value found in that tree.*/
struct Node *minValueNode(struct Node *node)
{
    struct Node *minNode = node;

    /* loop down to find the leftmost leaf */
    while (minNode && minNode->left != NULL)
        minNode = minNode->left;

    return minNode;
}

// Function to search a given Key in a given BST
struct Node *search(struct Node *node, int key)
{
    // Base Cases: root is null or Key is present at root
    if (node == NULL || node->data == key)
        return node;

    // Key is greater than root's value
    if (node->data < key)
        return search(node->right, key);

    // Key is smaller than root's value
    return search(node->left, key);
}

// Function to delete the value from the binary search tree return the new root
struct Node *delete (struct Node *node, int value)
{
    struct Node *temp;

    // base case
    if (node == NULL)
        return node;

    // If the key to be deleted is smaller than the root's key, then it lies in left subtree
    if (value < node->data)
        node->left = delete (node->left, value);

    // If the key to be deleted is greater than the root's key, then it lies in right subtree
    else if (value > node->data)
        node->right = delete (node->right, value);

    // If key is same as root's key, then This node will be deleted
    else
    {
        // If node has only one child or no child
        if (node->left == NULL)
        {
            temp = node;
            node = node->right;
            free(temp);
            return node;
        }
        else if (node->right == NULL)
        {
            temp = node;
            node = node->left;
            free(temp);
            return node;
        }

        // If node has two children:
        // Get the inorder successor(smallest element in the right subtree)
        struct Node *temp = minValueNode(node->right);

        // Copy the inorder successor value to this node
        node->data = temp->data;

        // Delete the inorder successor
        node->right = delete (node->right, temp->data);
    }
    return node;
}
