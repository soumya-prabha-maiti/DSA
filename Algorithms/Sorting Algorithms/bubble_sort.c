#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Sorts the array in ascending order
void bubble_sort(int *arr, int arrSize);
void merge(int *arr, int start, int mid, int end);
void merge_sort(int *arr, int start, int end);

int main()
{
    int choice, i, arrSize;
    int *arr;
    clock_t start, stop;
    FILE *fp;            

    // Opening the csv files
    fp = fopen("sorting.csv", "a");

    srand(time(0));

    printf("\t***BUBBLE SORT***");
    printf("\n1.Sort data from user input");
    printf("\n2.Sort completely unsorted data");
    printf("\n3.Sort nearly sorted data");
    printf("\n\nSelect an option:");
    scanf("%d", &choice);

    printf("\nEnter the number of elements:");
    scanf("%d", &arrSize);

    // Creating the array
    arr = (int *)malloc(arrSize * sizeof(int));

    //switch case for the different options
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
        {
            arr[i] = rand() % 100000;
        }
        break;

    case 3:
        for (i = 0; i < arrSize; i++)
        {
            arr[i] = rand() % 100000;
        }
        merge_sort(arr, arrSize / 2, arrSize - 1);
        break;

    default:
        printf("Invalid input");
        exit(0);
        break;
    }

    // Displaying the array before sorting
    printf("\n\nThe array before sorting is :\n");
    for (i = 0; i <= arrSize - 1; i++)
    {
        printf("%d ", arr[i]);
    }

    start = clock();
    // Sorting the array
    bubble_sort(arr, arrSize);
    stop = clock();

    // Displaying the sorted array
    printf("\n\nThe sorted array is :\n");
    for (i = 0; i <= arrSize - 1; i++)
    {
        printf("%d ", arr[i]);
    }

    // Time required 
    printf("\nTime taken to perform bubble sort: %f seconds", (double)(stop - start) / CLOCKS_PER_SEC);
    fprintf(fp, "%d,%f\n",arrSize, (double)(stop - start) / CLOCKS_PER_SEC);
    
    fclose(fp);
    return 0;
}

void bubble_sort(int *arr, int arrSize)
{
    int pass, j, temp, swapped;
    swapped = 1;
    for (pass = 1; pass <= arrSize - 1 && swapped == 1; pass++)
    {
        swapped = 0;
        for (j = 0; j <= arrSize - 1 - pass; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                // Swap arr[j] and arr[j + 1]
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;

                swapped = 1;
            }
        }
    }
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
