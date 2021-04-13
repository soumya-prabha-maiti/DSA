// C Program for evaluation of postfix expression using stack
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct node
{
    float data;
    struct node *next;
};

void push(struct node **topPtr, float value);
float pop(struct node **topPtr);
void display(struct node **topPtr);

int main()
{
    char ch;
    float value, operand1, operand2, result;
    struct node *top = NULL;
    printf("\n\t\tEVALUATION OF POSTFIX EXPRESSION");
    printf("\nNote: Enter the numbers(non-negative integers) and operators separated by comma. Use $ as the end of input.");
    printf("\nExample of postfix expression: \n\t 40,8,3,*,+,$ ");
    printf("\n\nEnter the postfix expression : ");
    while (1)
    {
        value = 0;
        scanf("%c", &ch);
        if (ch == '$')
            break;
        else if (ch >= '0' && ch <= '9')
        {
            value = ch - '0';
            while (1)
            {
                scanf("%c", &ch);
                if (ch == ',')
                    break;
                value = (value * 10) + (ch - '0');
            }
            push(&top, value);
            printf("\nPushed : %f", value);
            printf("\nThe stack after this operation is displayed below : ");
            display(&top);
        }
        else
        {
            operand2 = pop(&top);
            operand1 = pop(&top);
            printf("\nPopped : %f", operand2);
            printf("\nPopped : %f", operand1);
            switch (ch)
            {
            // result = operand1 operation operand2
            case '+':
                result = operand1 + operand2;
                break;
            case '-':
                result = operand1 - operand2;
                break;
            case '*':
                result = operand1 * operand2;
                break;
            case '/':
                if (operand2 == 0)
                {
                    printf("\n\nDIVISION BY ZERO IS NOT ALLOWED.\n");
                    exit(0);
                }
                result = (float)operand1 / operand2;
                break;
            case '^':
                result = pow(operand1, operand2); 
                break;

            default:
                printf("\nINVALID POSTFIX EXPRESSION\n");
                exit(0);
                break;
            }
            push(&top, result);
            printf("\nOperation : %f%c%f=%f", operand1, ch, operand2, result);
            printf("\nPushed : %f", result);
            printf("\nThe stack after this operation is displayed below :");
            display(&top);
            scanf("%c", &ch);
        }
    }

    value = pop(&top);
    if (top != NULL)
    {
        printf("\nINVALID POSTFIX EXPRESSION\n");
        exit(0);
    }
    printf("\nThe value of the expression is %f\n", value);
    return 0;
}

void push(struct node **topPtr, float value)
{
    struct node *newn;
    newn = (struct node *)malloc(sizeof(struct node));
    newn->data = value;
    newn->next = (*topPtr);
    (*topPtr) = newn;
}

float pop(struct node **topPtr)
{
    float value;
    struct node *ptr;
    if ((*topPtr) == NULL)
    {
        printf("\nINVALID POSTFIX EXPRESSION\n");
        exit(0);
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
            printf("\n\t%f", ptr->data);
            ptr = ptr->next;
        }
        printf("\n");
    }
}