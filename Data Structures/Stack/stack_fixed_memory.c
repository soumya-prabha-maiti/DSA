#include <stdio.h>
#include <stdlib.h>

#define STACKSIZE 5
//Such a small value is chosen to demonstrate the overflow condition

#define DELETE_FAILURE -32768
//The above value is to be chosen such that the value is never equal to any permissible element in the list

struct stack
{
    int items[STACKSIZE];
    int top;
};

void push(struct stack *stkPtr, int value);
int pop(struct stack *stkPtr);
void display(struct stack *stkPtr);

int main()
{
    int value, ch;
    struct stack stk, *stkPtr;
    stk.top = -1;
    stkPtr = &stk;
    printf("\nNote : This stack is designed to contain a maximum of %d elements\n", STACKSIZE);
    while (1)
    {
        printf("\n\t***STACK : FIXED MEMORY IMPLEMENTATION***");
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
            push(stkPtr, value);
            printf("\n\nThe stack after this operation is displayed below:");
            display(stkPtr);
            break;

        case 2:
            printf("\n\tSTACK : POP");
            value = pop(stkPtr);
            if (value != DELETE_FAILURE)
                printf("\nThe popped element is %d\n", value);
            printf("\nThe stack after this operation is displayed below:");
            display(stkPtr);
            break;

        case 3:
            printf("\n\tSTACK : DISPLAY");
            display(stkPtr);
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

void push(struct stack *stkPtr, int value)
{
    if (stkPtr->top == STACKSIZE - 1)
    {
        printf("Stack overflow. Unable to insert new element.\n");
        return;
    }
    else
    {
        (stkPtr->top) += 1;
        stkPtr->items[stkPtr->top] = value;
    }
}

int pop(struct stack *stkPtr)
{
    int value;
    if (stkPtr->top == -1)
    {
        printf("\nStack underflow. Nothing to delete.\n");
        return DELETE_FAILURE;
    }
    else
    {
        value = stkPtr->items[stkPtr->top];
        (stkPtr->top)--;
        return value;
    }
}

void display(struct stack *stkPtr)
{
    int i;
    if (stkPtr->top == -1)
    {
        printf("\nStack underflow: Stack is empty\n");
    }
    else
    {
        printf("\nThe stack elements are:");
        for (i = stkPtr->top; i >= 0; i--)
        {
            printf("\n\t%d", stkPtr->items[i]);
        }
        printf("\n");
    }
}