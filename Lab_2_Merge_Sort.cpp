#include <cstdio>

constexpr int MAX_SIZE = 100;

/**
 * @brief Merges two adjacent sorted subarrays into a single sorted subarray.
 *
 * The left subarray spans arr[low..mid] and the right subarray spans
 * arr[mid+1..high]. The merged result is written back into arr[low..high].
 *
 * @param arr  Array containing the subarrays.
 * @param low  Start index of the left subarray.
 * @param mid  End index of the left subarray.
 * @param high End index of the right subarray.
 */
void merge(int arr[], int low, int mid, int high)
{
    int temp[MAX_SIZE];
    int i = low;
    int j = mid + 1;
    int k = low;

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

    while (i <= mid)
    {
        temp[k++] = arr[i++];
    }

    while (j <= high)
    {
        temp[k++] = arr[j++];
    }

    for (i = low; i <= high; ++i)
    {
        arr[i] = temp[i];
    }
}

/**
 * @brief Sorts an array using the merge sort algorithm.
 *
 * Recursively divides the range [low..high] into halves, sorts each half,
 * and merges them back together.
 *
 * @param arr  Array to be sorted.
 * @param low  Start index of the range.
 * @param high End index of the range.
 */
void mergeSort(int arr[], int low, int high)
{
    if (low < high)
    {
        int mid = low + (high - low) / 2;

        mergeSort(arr, low, mid);
        mergeSort(arr, mid + 1, high);
        merge(arr, low, mid, high);
    }
}

/**
 * @brief Entry point: reads integers, sorts them, and prints the result.
 */
int main()
{
    int arr[MAX_SIZE];
    int n;

    std::printf("Enter number of elements: ");
    std::scanf("%d", &n);

    std::printf("Enter elements:\n");
    for (int i = 0; i < n; ++i)
    {
        std::scanf("%d", &arr[i]);
    }

    mergeSort(arr, 0, n - 1);

    std::printf("\nSorted array:\n");
    for (int i = 0; i < n; ++i)
    {
        std::printf("%d ", arr[i]);
    }
    std::printf("\n");

    return 0;
}