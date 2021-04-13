#include <stdio.h>
#include <stdlib.h>

#define DELETE_FAILURE -32768
//The above value is to be chosen such that the value is never equal to any permissible element in the queue

struct node
{
    int data;
    struct node *next;
};
void insert(struct node **frontPtr, struct node **rearPtr, int value);
int delete (struct node **frontPtr, struct node **rearPtr);
void display(struct node **frontPtr, struct node **rearPtr);
int main()
{
    struct node *front = NULL, *rear = NULL;
    int value, ch;

    while (1)
    {
        printf("\n\t***QUEUE : DYNAMIC MEMORY IMPLEMENTATION***");
        printf("\n1.INSERT");
        printf("\n2.DELETE");
        printf("\n3.DISPLAY");
        printf("\n0.EXIT");

        printf("\n\nEnter your choice:");
        scanf("%d", &ch);
        switch (ch)
        {
        case 1:
            printf("\n\tQUEUE : INSERT");
            printf("\nEnter data:");
            scanf("%d", &value);
            insert(&front, &rear, value);
            printf("\n\nThe queue after this operation is displayed below:");
            display(&front, &rear);
            break;

        case 2:
            printf("\n\tQUEUE : DELETE");
            value = delete (&front, &rear);
            if (value != DELETE_FAILURE)
                printf("\nThe deleted element is %d\n", value);
            printf("\nThe queue after this operation is displayed below:");
            display(&front, &rear);
            break;

        case 3:
            printf("\n\tQUEUE : DISPLAY");
            display(&front, &rear);
            break;
        case 0:
            exit(0);
        default:
            printf("Invalid Entry! Please try again.\n");
            break;
        }
    }

    return 0;
}

void insert(struct node **frontPtr, struct node **rearPtr, int value)
{
    struct node *newn;
    newn = (struct node *)malloc(sizeof(struct node));
    newn->data = value;
    newn->next = NULL;
    if ((*frontPtr) == NULL)
    {
        (*frontPtr) = newn;
        (*rearPtr) = newn;
    }
    else
    {
        (*rearPtr)->next = newn;
        (*rearPtr) = (*rearPtr)->next;
    }
}
int delete (struct node **frontPtr, struct node **rearPtr)
{
    int value;
    struct node *ptr;
    if ((*frontPtr) == NULL)
    {
        printf("\nQueue underflow. Nothing to delete.\n");
        return DELETE_FAILURE;
    }
    else
    {
        ptr = (*frontPtr);
        (*frontPtr) = (*frontPtr)->next;
        if ((*frontPtr) == NULL)
            (*rearPtr) = NULL;
        value = ptr->data;
        free(ptr);
        ptr = NULL;
        return value;
    }
}

void display(struct node **frontPtr, struct node **rearPtr)
{
    struct node *ptr;
    if ((*frontPtr) == NULL)
    {
        printf("\nQueue underflow: Queue is empty.\n");
        return;
    }
    else
    {
        ptr = (*frontPtr);
        printf("\nThe queue elements are:\n");
        while (ptr != NULL)
        {
            printf("%d ", ptr->data);
            ptr = ptr->next;
        }
        printf("\n");
    }
}