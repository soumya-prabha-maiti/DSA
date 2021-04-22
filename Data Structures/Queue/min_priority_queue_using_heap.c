// Program : Min prriority queue using binary min heap
#include <stdio.h>
#include <stdlib.h>

#define HEAP_MAX_SIZE 5       //Such a small value is chosen to demonstrate the overflow condition
#define DELETE_FAILURE -32768 //This value is to be chosen such that the value is never equal to any permissible element in the queue

//Given below is the structure of every element or item in the priority queue . Every item consists of two parts - 1.the data or value, and 2.the priority associated with it.
struct item
{
    int value;
    int priority;
};

// Given below is the structure of the binary min heap to implement the priority queue
struct binaryMinHeap
{
    int lastOccupiedIndex;
    struct item items[HEAP_MAX_SIZE];
};

int parent(int i);
int leftChild(int i);
int rightChild(int i);
void insert(struct binaryMinHeap *heapPtr, struct item newItem);
void display_min(struct binaryMinHeap *heapPtr);
void minHeapify(struct binaryMinHeap *heapPtr, int i);
struct item extract_min(struct binaryMinHeap *heapPtr);
void display(struct binaryMinHeap *heapPtr);


int main()
{
    struct binaryMinHeap heap;
    int value, priority, ch;
    struct item item;
    heap.lastOccupiedIndex=-1;

    printf("\nNote : This is a min priority queue , element with lowest value of priority is deleted first.\nThis queue is designed to contain a maximum of %d elements.\n", HEAP_MAX_SIZE);
    while (1)
    {
        printf("\n\t***MIN PRIORITY QUEUE : HEAP IMPLEMENTATION***");
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
            scanf("%d", &item.value);
            printf("\nEnter priority(positive integer):");
            scanf("%d", &item.priority);
            insert(&heap,item);
            printf("\n\nThe queue after this operation is displayed below:");
            display(&heap);
            break;

        case 2:
            printf("\n\tMIN PRIORITY QUEUE : DISPLAY MIN");
            display_min(&heap);
            printf("\n\nThe queue after this operation is displayed below:");
            display(&heap);
            break;
        case 3:
            printf("\n\tMIN PRIORITY QUEUE : EXTRACT MIN");
            item = extract_min(&heap);
            if (item.value != DELETE_FAILURE && item.priority!= DELETE_FAILURE)
                printf("\nThe deleted element is %d having priority %d.\n", item.value,item.priority);
            printf("\nThe queue after this operation is displayed below:");
            display(&heap);
            break;

        case 4:
            printf("\n\tMIN PRIORITY QUEUE : DISPLAY");
            display(&heap);
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




// Returns the index of parent of node at index i
int parent(int i) { return (i - 1) / 2; }

// Returns the index of left child of node at index i
int leftChild(int i) { return (2 * i + 1); }

// Returns the index of right child of node at index i
int rightChild(int i) { return (2 * i + 2); }

// Inserts a new element into the heap
void insert(struct binaryMinHeap *heapPtr, struct item newItem)
{
    int i;
    struct item temp;
    if ((heapPtr->lastOccupiedIndex) == HEAP_MAX_SIZE - 1)
    {
        printf("Priority queue overflow. Unable to insert new element.\n");
        return;
    }

    (heapPtr->lastOccupiedIndex)++;
    heapPtr->items[heapPtr->lastOccupiedIndex] = newItem;

    // Checking and fixing the min heap property if violated
    i = heapPtr->lastOccupiedIndex;
    while ((i != 0) && (heapPtr->items[i].priority < heapPtr->items[parent(i)].priority))
    {
        // As long as the parent's priority is more , swapping is done
        // swap(heapPtr->items[i],heapPtr->items[parent(i)])
        temp = heapPtr->items[i];
        heapPtr->items[i] = heapPtr->items[parent(i)];
        heapPtr->items[parent(i)] = temp;

        i = parent(i);
    }
}

// Displays the min priority element without deleting it.
void display_min(struct binaryMinHeap *heapPtr)
{

    if (heapPtr->lastOccupiedIndex == -1) //if queue is empty
    {
        printf("\nPriority queue underflow: Priority queue is empty.\n");
    }
    else
    {
        printf("\nThe minimum priority element is %d.\nIts priority value is %d.", heapPtr->items[0].value,heapPtr->items[0].priority);
    }
}

// A recursive function to heapify a subtree with the root at given index
void minHeapify(struct binaryMinHeap *heapPtr, int i)
{
    int lChild, rChild, smallest;
    struct item temp;
    lChild = leftChild(i);
    rChild = rightChild(i);
    smallest = i;
    if (lChild <= heapPtr->lastOccupiedIndex && heapPtr->items[lChild].priority < heapPtr->items[smallest].priority)
        smallest = lChild;
    if (rChild <= heapPtr->lastOccupiedIndex && heapPtr->items[rChild].priority < heapPtr->items[smallest].priority)
        smallest = rChild;
    if (smallest != i)
    {
        // swap(heapPtr->items[i], heapPtr->items[smallest]);
        temp = heapPtr->items[i];
        heapPtr->items[i] = heapPtr->items[smallest];
        heapPtr->items[smallest] = temp;

        minHeapify(heapPtr, smallest);
    }
}

// Deletes the min priority element
struct item extract_min(struct binaryMinHeap *heapPtr)
{
    struct item deletedItem;
    if (heapPtr->lastOccupiedIndex == -1)
    {
        printf("\nPriority queue underflow. Nothing to delete.\n");
        deletedItem.value = DELETE_FAILURE;
        deletedItem.priority = DELETE_FAILURE;
        return deletedItem;
    }

    if (heapPtr->lastOccupiedIndex == 0)
    {
        (heapPtr->lastOccupiedIndex)--;
        return heapPtr->items[0];
    }

    // Store the minimum priority item, and remove it from heap
    deletedItem = heapPtr->items[0];
    heapPtr->items[0] = heapPtr->items[heapPtr->lastOccupiedIndex];
    (heapPtr->lastOccupiedIndex)--;
    minHeapify(heapPtr, 0);

    return deletedItem;
}


void display(struct binaryMinHeap *heapPtr)
{
    int i;
    if (heapPtr->lastOccupiedIndex == -1) //if queue is empty
    {
        printf("\nPriority queue underflow: Priority queue is empty\n");
    }
    else
    {
        printf("\nThe elements in the priority queue are shown below in the format (VALUE|PRIORITY):\n");
        for (i = 0; i <= (heapPtr->lastOccupiedIndex); i++)
        {
            printf("(%d|%d) ", heapPtr->items[i].value, heapPtr->items[i].priority);
        }
        printf("\n");
    }
}

