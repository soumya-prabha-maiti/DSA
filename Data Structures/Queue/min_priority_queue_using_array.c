// Program : Min priority queue using array
#include <stdio.h>
#include <stdlib.h>

#define QUEUE_MAX_SIZE 5      //Such a small value is chosen to demonstrate the overflow condition
#define DELETE_FAILURE -32768 //This value is to be chosen such that the value is never equal to any permissible element in the queue

//Given below is the structure of every element or item in the priority queue . Every item consists of two parts - 1.the data or value, and 2.the priority associated with it.
struct item
{
    int value;
    int priority;
};

// Given below is the structure of the priority queue implemented using array
struct queue
{
    int rear;
    struct item items[QUEUE_MAX_SIZE];
};

void insert(struct queue *qPtr, int value, int priority);
int find_min_index(struct queue *qPtr);
void display_min(struct queue *qPtr);
struct item extract_min(struct queue *qPtr);
void display(struct queue *qPtr);

int main()
{
    struct queue q;
    int value, priority, ch;
    struct item deletedItem;
    q.rear = -1;

    printf("\nNote : This is a min priority queue , element with lowest value of priority is deleted first.\nThis queue is designed to contain a maximum of %d elements\n", QUEUE_MAX_SIZE);
    while (1)
    {
        printf("\n\t***MIN PRIORITY QUEUE : ARRAY IMPLEMENTATION***");
        printf("\n1.INSERT");
        printf("\n2.DISPLAY MIN");
        printf("\n3.EXTRACT/DELETE MIN");
        printf("\n4.DISPLAY");
        printf("\n0.EXIT");

        printf("\n\nEnter your choice:");
        scanf("%d", &ch);
        switch (ch)
        {
        case 1:
            printf("\n\tMIN PRIORITY QUEUE : INSERT");
            printf("\nEnter data:");
            scanf("%d", &value);
            printf("\nEnter priority(positive integer):");
            scanf("%d", &priority);
            insert(&q, value, priority);
            printf("\n\nThe queue after this operation is displayed below:");
            display(&q);
            break;

        case 2:
            printf("\n\tMIN PRIORITY QUEUE : DISPLAY MIN");
            display_min(&q);
            printf("\n\nThe queue after this operation is displayed below:");
            display(&q);
            break;
        case 3:
            printf("\n\tMIN PRIORITY QUEUE : EXTRACT MIN");
            deletedItem = extract_min(&q);
            if (deletedItem.value != DELETE_FAILURE && deletedItem.priority!= DELETE_FAILURE)
                printf("\nThe deleted element is %d having priority %d.\n", deletedItem.value,deletedItem.priority);
            printf("\nThe queue after this operation is displayed below:");
            display(&q);
            break;

        case 4:
            printf("\n\tMIN PRIORITY QUEUE : DISPLAY");
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

//Inserts a new element in the priority queue
void insert(struct queue *qPtr, int value, int priority)
{
    if (qPtr->rear == QUEUE_MAX_SIZE - 1)
    {
        printf("Priority queue overflow. Unable to insert new element.\n");
        return;
    }
    else
    {
        (qPtr->rear) += 1;
        qPtr->items[qPtr->rear].value = value;
        qPtr->items[qPtr->rear].priority = priority;
    }
}

//Returns the index at which the element with min priority is present. In case of multiple elements with same priority, returns the element which occurs first
int find_min_index(struct queue *qPtr)
{
    int i, min_index = 0;
    //No need to check for underflow as this function is called only when there is no underflow
    for (i = 0; i <= qPtr->rear; i++)
    {
        if ((qPtr->items[i].priority) < (qPtr->items[min_index].priority))
            min_index = i;
    }
    return min_index;
}

//Displays the min priority element without deleting it.If there are multiple elements with same priority, it displays the first one.
void display_min(struct queue *qPtr)
{
    int min_index;
    if (qPtr->rear == -1) //if queue is empty
    {
        printf("\nPriority queue underflow: Priority queue is empty.\n");
    }
    else
    {
        min_index = find_min_index(qPtr);
        printf("\nThe element with minimum priority value is %d.\nIts priority value is %d.", qPtr->items[min_index].value, qPtr->items[min_index].priority);
    }
}

// Deletes the min priority element.If there are multiple elements with same priority, it deletes the first one.
struct item extract_min(struct queue *qPtr)
{
    int i, min_index;
    struct item deletedItem;
    if (qPtr->rear == -1) //if queue is empty
    {
        printf("\nPriority queue underflow. Nothing to delete.\n");
        deletedItem.value = DELETE_FAILURE;
        deletedItem.priority = DELETE_FAILURE;
    }
    else
    {
        min_index = find_min_index(qPtr);
        deletedItem = qPtr->items[min_index];
        for (i = min_index; i < (qPtr->rear); i++)
        {
            qPtr->items[i] = qPtr->items[i + 1];
        }
        (qPtr->rear) = (qPtr->rear) - 1;
    }
    return deletedItem;
}

void display(struct queue *qPtr)
{
    int i;
    if (qPtr->rear == -1) //if queue is empty
    {
        printf("\nPriority queue underflow: Priority queue is empty\n");
    }
    else
    {
        printf("\nThe elements in the priority queue are shown below in the format (VALUE|PRIORITY):\n");
        for (i = 0; i <= (qPtr->rear); i++)
        {
            printf("(%d|%d) ", qPtr->items[i].value, qPtr->items[i].priority);
        }
        printf("\n");
    }
}