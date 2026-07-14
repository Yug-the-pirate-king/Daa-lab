#include <stdio.h>

/**
 * @brief Sorts an array of integers in ascending order using the selection sort algorithm.
 *
 * The algorithm repeatedly selects the minimum element from the unsorted portion
 * of the array and swaps it with the element at the current boundary.
 *
 * @param arr The array to be sorted.
 * @param n   The number of elements in the array. Must be non-negative.
 */
void selectionSort(int arr[], int n)
{
    // A subarray of size 0 or 1 is already sorted.
    if (n <= 1)
    {
        return;
    }

    for (int i = 0; i < n - 1; i++)
    {
        int minIdx = i;

        // Find the index of the minimum element in the unsorted portion.
        for (int j = i + 1; j < n; j++)
        {
            if (arr[j] < arr[minIdx])
            {
                minIdx = j;
            }
        }

        // Swap the found minimum element with the current boundary element.
        if (minIdx != i)
        {
            int temp = arr[minIdx];
            arr[minIdx] = arr[i];
            arr[i] = temp;
        }
    }
}

/**
 * @brief Prints the elements of an integer array separated by spaces.
 *
 * @param arr The array to print.
 * @param n   The number of elements in the array.
 */
void printArray(const int arr[], int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main()
{
    int arr[50];
    int n;

    printf("Enter number of elements: ");
    if (scanf("%d", &n) != 1)
    {
        printf("Error: Invalid input for number of elements.\n");
        return 1;
    }

    if (n <= 0 || n > 50)
    {
        printf("Error: Number of elements must be between 1 and 50.\n");
        return 1;
    }

    printf("Enter elements:\n");
    for (int i = 0; i < n; i++)
    {
        if (scanf("%d", &arr[i]) != 1)
        {
            printf("Error: Invalid input for element %d.\n", i + 1);
            return 1;
        }
    }

    selectionSort(arr, n);

    printf("\nSorted array:\n");
    printArray(arr, n);

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