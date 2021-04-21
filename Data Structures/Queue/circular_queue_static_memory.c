#include <stdio.h>
#include <stdlib.h>

#define QUEUE_MAX_SIZE 5
//Such a small value is chosen to demonstrate the overflow condition

#define DELETE_FAILURE -32768
//The above value is to be chosen such that the value is never equal to any permissible element in the queue

struct queue
{
    int front, rear;
    int items[QUEUE_MAX_SIZE];
};

void display(struct queue *qPtr);
int delete (struct queue *qPtr);
void insert(struct queue *qPtr, int value);

int main()
{
    struct queue q;
    int value, ch;
    q.front = -1;
    q.rear = -1;

    printf("\nNote : This queue is designed to contain a maximum of %d elements\n", QUEUE_MAX_SIZE);
    while (1)
    {
        printf("\n\t***CIRCULAR QUEUE***");
        // printf("\n\t***CIRCULAR QUEUE : FIXED MEMORY IMPLEMENTATION***");
        printf("\n1.INSERT");
        printf("\n2.DELETE");
        printf("\n3.DISPLAY");
        printf("\n0.EXIT");

        printf("\n\nEnter your choice:");
        scanf("%d", &ch);
        switch (ch)
        {
        case 1:
            printf("\n\tCIRCULAR QUEUE : INSERT");
            printf("\nEnter data:");
            scanf("%d", &value);
            insert(&q, value);
            printf("\n\nThe queue after this operation is displayed below:");
            display(&q);
            break;

        case 2:
            printf("\n\tCIRCULAR QUEUE : DELETE");
            value = delete (&q);
            if (value != DELETE_FAILURE)
                printf("\nThe deleted element is %d\n", value);
            printf("\nThe queue after this operation is displayed below:");
            display(&q);
            break;

        case 3:
            printf("\n\tCIRCULAR QUEUE : DISPLAY");
            display(&q);
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

void insert(struct queue *qPtr, int value)
{
    if (((qPtr->rear == QUEUE_MAX_SIZE - 1) && (qPtr->front == 0)) || ((qPtr->front) - (qPtr->rear) == 1))
    {
        printf("Queue overflow. Unable to insert new element.\n");
        return;
    }
    else
    {
        if (qPtr->front == -1) //if queue is empty
            qPtr->front = 0;

        (qPtr->rear) += 1;
        if ((qPtr->rear) == QUEUE_MAX_SIZE)
            (qPtr->rear) = 0;
        qPtr->items[qPtr->rear] = value;
    }
}

int delete (struct queue *qPtr)
{
    int value;
    if (qPtr->rear == -1) //if queue is empty
    {
        printf("\nQueue underflow. Nothing to delete.\n");
        return DELETE_FAILURE;
    }
    else
    {
        value = qPtr->items[qPtr->front];
        if ((qPtr->front) == (qPtr->rear))
        {
            (qPtr->front) = -1;
            (qPtr->rear) == -1;
        }
        else
        {
            (qPtr->front)++;
            if ((qPtr->front) == QUEUE_MAX_SIZE)
                (qPtr->front) = 0;
        }

        return value;
    }
}

void display(struct queue *qPtr)
{
    int i;
    if((qPtr->front)<=(qPtr->rear))
    {
        for(i=qPtr->front;i<=qPtr->rear;i++)
        {
            printf("%d ",qPtr->items[i]);
        }
    }
    else
    {
        for(i=qPtr->front;i<=QUEUE_MAX_SIZE-1;i++)
        {
            printf("%d ",qPtr->items[i]);
        }
        for(i=0;i<=qPtr->rear;i++)
        {
            printf("%d ",qPtr->items[i]);
        }
    }
}