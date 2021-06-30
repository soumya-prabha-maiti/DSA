#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NOT_FOUND -1

int linear_search(int *arr, int arrSize, int search);

int main()
{
    int arrSize, search, i, choice,searchIndex;
    int *arr;
    clock_t start, stop;
    FILE *fl;

    // Opening the csv file
    fl = fopen("linear_search.csv", "a");

    srand(time(0));

    // Menu
    printf("\t***LINEAR SEARCH***");
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

    // Displaying the array
    printf("\n\nThe array is :\n");
    for (i = 0; i <= arrSize - 1; i++)
    {
        printf("%d ", arr[i]);
    }


    // Input the element to search
    printf("\nEnter the element to search:");
    scanf("%d", &search);


    // Searching the array
    // linear_search
    start = clock();
    searchIndex=linear_search(arr, arrSize, search);
    stop = clock();

    if(searchIndex==NOT_FOUND)
         printf("\n%d not found in the array",search);
    else
        printf("\n%d found at index %d in the array (Element at the beginning has index=0).",search,searchIndex);
    printf("\nTime taken: %f",(double)(stop - start) / CLOCKS_PER_SEC);
    fprintf(fl, "%d, %f\n", arrSize, (double)(stop - start) / CLOCKS_PER_SEC);

    fclose(fl);
    return 0;
}

// Returns the index of first occurrence of the element being searched, if found 
int linear_search(int *arr, int arrSize, int search)
{
    int i;
    for (i = 0; i < arrSize; i++)
    {
        if (arr[i] == search)
        {
            return i;
        }
    }
    if (i == arrSize)
    {
        return NOT_FOUND;
    }
}