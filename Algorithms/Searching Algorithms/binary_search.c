#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NOT_FOUND -1

int binary_search(int *arr, int arrSize, int search);
void merge(int *arr, int start, int mid, int end);
void merge_sort(int *arr, int start, int end);

int main()
{
    int arrSize, search, i,choice,searchIndex;
    int *arr;
    clock_t start, stop;
    FILE *fb;

    // Opening the csv files
    fb = fopen("binary_search.csv", "a");

    srand(time(0));

    // Menu
    printf("\t***BINARY SEARCH***");
    printf("\n1.Search user data");
    printf("\n2.Search randomly generated data");
    printf("\nEnter your choice:");
    scanf("%d", &choice);

    // Creating the array
    printf("Enter the number of elements:");
    scanf("%d", &arrSize);
    arr = (int *)malloc(arrSize * sizeof(int));

    switch (choice)
    {
    case 1:
        for (i = 0; i < arrSize; i++)
        {
            printf("Enter an integer for arr[%d]:", i);
            scanf("%d", &arr[i]);
        }
        break;
    case 2:
        for (i = 0; i < arrSize; i++)
            arr[i] = rand() % 1000;
        break;

    default:
        printf("Invalid input");
        exit(0);
    }

    // Sorting the array in ascending order
    merge_sort(arr, 0, arrSize - 1);

    // Displaying the array
    printf("\n\nThe array(after sorting) is :\n");
    for (i = 0; i <= arrSize - 1; i++)
    {
        printf("%d ", arr[i]);
    }
    
    // Input the element to search
    printf("\nEnter the element to search:");
    scanf("%d", &search);


    // Searching the array
    // binary_search
    start = clock();
    searchIndex=binary_search(arr, arrSize, search);
    stop = clock();

    if(searchIndex==NOT_FOUND)
         printf("\n%d not found in the array",search);
    else
        printf("\n%d found at index %d in the array (Element at the beginning has index=0).",search,searchIndex);
    printf("\nTime taken: %f",(double)(stop - start) / CLOCKS_PER_SEC);
    fprintf(fb, "%d, %f\n", arrSize, (double)(stop - start) / CLOCKS_PER_SEC);

    fclose(fb);
    return 0;
}

int binary_search(int *arr, int arrSize, int search)
{
    // arr is sorted in ascending order
    int start = 0, end = arrSize - 1, mid;
    while (start <= end)
    {
        mid = (start + end) / 2;
        if (arr[mid] == search)
        {
            return mid;
        }
        else if (arr[mid] < search)
        {
            start = mid + 1;
        }
        else
        {
            end = mid - 1;
        }
    }
    return NOT_FOUND;
}

void merge(int *arr, int start, int mid, int end)
{
    int *leftArr, *rightArr, leftSize, rightSize, i, x, y;
    leftSize = mid - start + 1;
    rightSize = end - mid;
    leftArr = (int *)malloc(leftSize * sizeof(int));
    rightArr = (int *)malloc(rightSize * sizeof(int));
    for (i = start, x = 0; i <= mid; i++, x++)
        leftArr[x] = arr[i];
    for (i = mid + 1, y = 0; i <= end; i++, y++)
        rightArr[y] = arr[i];

    x = 0;
    y = 0;
    for (i = start; i <= end; i++)
    {
        if (x == leftSize)
        {
            arr[i] = rightArr[y];
            y++;
        }
        else if (y == rightSize)
        {
            arr[i] = leftArr[x];
            x++;
        }
        else if (leftArr[x] <= rightArr[y])
        {
            arr[i] = leftArr[x];
            x++;
        }
        else
        {
            arr[i] = rightArr[y];
            y++;
        }
    }
}

void merge_sort(int *arr, int start, int end)
{
    int mid;
    if (start == end)
        return;

    mid = (start + end) / 2;
    merge_sort(arr, start, mid);   //sorts arr from index start to mid
    merge_sort(arr, mid + 1, end); //sorts arr from mid+1 to end
    merge(arr, start, mid, end);   //merges (start to mid) and (mid+1 to end)
}
