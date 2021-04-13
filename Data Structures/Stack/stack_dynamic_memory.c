#include <stdio.h>
#include <stdlib.h>

#define DELETE_FAILURE -32768
//The above value is to be chosen such that the value is never equal to any permissible element in the stack


struct node
{
    int data;
    struct node *next;
};

void push(struct node **topPtr, int value);
int pop(struct node **topPtr);
void display(struct node **topPtr);

int main()
{
    int value, ch;
    struct node *top = NULL;

    while (1)
    {
        printf("\n\t***STACK : DYNAMIC MEMORY IMPLEMENTATION***");
        printf("\n1.PUSH");
        printf("\n2.POP");
        printf("\n3.DISPLAY");
        printf("\n0.EXIT");

        printf("\n\nEnter your choice:");
        scanf("%d", &ch);
        switch (ch)
        {

        case 1:
            printf("\n\tSTACK : PUSH");
            printf("\nEnter data:");
            scanf("%d", &value);
            push(&top, value);
            printf("\n\nThe stack after this operation is displayed below:");
            display(&top);
            break;

        case 2:
            printf("\n\tSTACK : POP");
            value = pop(&top);
            if (value != DELETE_FAILURE)
                printf("\nThe popped element is %d.\n", value);
            printf("\n\nThe stack after this operation is displayed below:");
            display(&top);
            break;

        case 3:
            printf("\n\tSTACK : DISPLAY");
            display(&top);
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

void push(struct node **topPtr, int value)
{
    struct node *newn;
    newn = (struct node *)malloc(sizeof(struct node));
    newn->data = value;
    newn->next = (*topPtr);
    (*topPtr) = newn;
}

int pop(struct node **topPtr)
{
    int value;
    struct node *ptr;
    if ((*topPtr) == NULL)
    {
        printf("\nStack underflow. Nothing to delete.\n");
        return DELETE_FAILURE;
    }
    else
    {
        ptr = (*topPtr);
        (*topPtr) = (*topPtr)->next;
        value = ptr->data;
        free(ptr);
        ptr = NULL;
        return value;
    }
}

void display(struct node **topPtr)
{
    struct node *ptr;
    if ((*topPtr) == NULL)
    {
        printf("\nStack underflow: Stack is empty.\n");
        return;
    }
    else
    {
        ptr = (*topPtr);
        printf("\nThe stack elements are:");
        while (ptr != NULL)
        {
            printf("\n\t%d", ptr->data);
            ptr = ptr->next;
        }
        printf("\n");
    }
}