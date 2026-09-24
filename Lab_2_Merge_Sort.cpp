#include <iostream>
#include <vector>

// Merges two sorted subarrays arr[low..mid] and arr[mid+1..high]
// back into a single sorted subarray arr[low..high].
void merge(std::vector<int> &arr, int low, int mid, int high)
{
    int left = low;       // Current index in the left subarray
    int right = mid + 1;  // Current index in the right subarray

    // Temporary buffer sized exactly for the current subarray.
    std::vector<int> temp;
    temp.reserve(static_cast<std::size_t>(high - low + 1));

    // Pick the smaller element from either subarray until one is exhausted.
    while (left <= mid && right <= high)
    {
        if (arr[left] <= arr[right])
        {
            temp.push_back(arr[left++]);
        }
        else
        {
            temp.push_back(arr[right++]);
        }
    }

    // Copy any remaining elements from the left subarray.
    while (left <= mid)
    {
        temp.push_back(arr[left++]);
    }

    // Copy any remaining elements from the right subarray.
    while (right <= high)
    {
        temp.push_back(arr[right++]);
    }

    // Write the merged values back into the original array.
    for (std::size_t idx = 0; idx < temp.size(); ++idx)
    {
        arr[static_cast<std::size_t>(low) + idx] = temp[idx];
    }
}

// Recursively splits the array and merges the sorted halves.
void mergeSort(std::vector<int> &arr, int low, int high)
{
    if (low < high)
    {
        // Midpoint calculation avoids potential overflow.
        int mid = low + (high - low) / 2;

        mergeSort(arr, low, mid);      // Sort the left half
        mergeSort(arr, mid + 1, high); // Sort the right half
        merge(arr, low, mid, high);    // Merge the two sorted halves
    }
}

int main()
{
    int n = 0;

    std::cout << "Enter number of elements: ";
    if (!(std::cin >> n) || n <= 0)
    {
        std::cerr << "Invalid input: please enter a positive integer.\n";
        return 1;
    }

    // Dynamic container removes the fixed-size array limitation.
    std::vector<int> arr(static_cast<std::size_t>(n));

    std::cout << "Enter elements:\n";
    for (int i = 0; i < n; ++i)
    {
        if (!(std::cin >> arr[static_cast<std::size_t>(i)]))
        {
            std::cerr << "Invalid input for element " << (i + 1) << ".\n";
            return 1;
        }
    }

    mergeSort(arr, 0, n - 1);

    std::cout << "\nSorted array:\n";
    for (int i = 0; i < n; ++i)
    {
        std::cout << arr[static_cast<std::size_t>(i)]
                  << (i + 1 == n ? '\n' : ' ');
    }

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