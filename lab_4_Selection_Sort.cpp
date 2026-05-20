#include <stdio.h>

void selectionSort(int arr[], int n)
{
    int i, j, minIdx, temp;

    // Move boundary of unsorted subarray one by one
    for (i = 0; i < n - 1; i++)
    {
        minIdx = i; // Assume the first element is the minimum

        // Find the absolute minimum element in the remaining unsorted array
        for (j = i + 1; j < n; j++)
        {
            if (arr[j] < arr[minIdx])
            {
                minIdx = j;
            }
        }

        // Swap the found minimum element with the first element
        temp = arr[minIdx];
        arr[minIdx] = arr[i];
        arr[i] = temp;
    }
}

int main()
{
    int arr[50], n, i;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    printf("Enter elements:\n");
    for (i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }

    selectionSort(arr, n);

    printf("\nSorted array:\n");
    for (i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}

// Enter number of elements: 5
// Enter elements:
// 64
// 25
// 12
// 22
// 11
//
// Sorted array:
// 11 12 22 25 64