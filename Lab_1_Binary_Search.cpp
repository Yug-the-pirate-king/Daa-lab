#include <stdio.h>

int binarySearch(int arr[], int n, int target)
{
    int low = 0, high = n - 1;

    while (low <= high)
    {
        int mid = low + (high - low) / 2; // Avoids potential integer overflow

        if (arr[mid] == target)
        {
            return mid; // Target found, return index
        }
        if (arr[mid] < target)
        {
            low = mid + 1; // Target is in the right half
        }
        else
        {
            high = mid - 1; // Target is in the left half
        }
    }
    return -1; // Target not found
}

int main()
{
    int arr[50], n, target, i;

    printf("Enter number of elements (must be sorted): ");
    scanf("%d", &n);

    printf("Enter elements in sorted order:\n");
    for (i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }

    printf("Enter target element to search: ");
    scanf("%d", &target);

    int result = binarySearch(arr, n, target);

    if (result != -1)
    {
        printf("\nElement found at index: %d\n", result);
    }
    else
    {
        printf("\nElement not found in the array.\n");
    }

    return 0;
}

// Enter number of elements (must be sorted): 5
// Enter elements in sorted order:
// 10
// 20
// 30
// 40
// 50
// Enter target element to search: 40
//
// Element found at index: 3