#include <stdio.h>

// Merges two sorted subarrays into one sorted array
void merge(int arr[], int low, int mid, int high)
{
    int temp[100];
    int i = low;     // Starting index for left subarray
    int j = mid + 1; // Starting index for right subarray
    int k = low;     // Starting index for temporary array

    while (i <= mid && j <= high)
    {
        if (arr[i] <= arr[j])
        {
            temp[k++] = arr[i++];
        }
        else
        {
            temp[k++] = arr[j++];
        }
    }

    // Copy remaining elements of left subarray if any
    while (i <= mid)
    {
        temp[k++] = arr[i++];
    }

    // Copy remaining elements of right subarray if any
    while (j <= high)
    {
        temp[k++] = arr[j++];
    }

    // Copy the sorted elements back into original array
    for (i = low; i <= high; i++)
    {
        arr[i] = temp[i];
    }
}

void mergeSort(int arr[], int low, int high)
{
    if (low < high)
    {
        int mid = low + (high - low) / 2;

        mergeSort(arr, low, mid);      // Sort left half
        mergeSort(arr, mid + 1, high); // Sort right half
        merge(arr, low, mid, high);    // Merge both sorted halves
    }
}

int main()
{
    int arr[100], n, i;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    printf("Enter elements:\n");
    for (i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }

    mergeSort(arr, 0, n - 1);

    printf("\nSorted array:\n");
    for (i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}

// Enter number of elements: 6
// Enter elements:
// 12
// 11
// 13
// 5
// 6
// 7
//
// Sorted array:
// 5 6 7 11 12 13