#include <stdio.h>
#include <limits.h>

struct min_max
{
    int min;
    int max;
};

struct min_max find_min_max(const int arr[], int low, int high)
{
    struct min_max result, mml, mmr;
    int mid;

    if (arr == NULL || low > high) {
        result.min = INT_MAX;
        result.max = INT_MIN;
        return result;
    }

    if (low == high) {
        result.min = arr[low];
        result.max = arr[low];
        return result;
    }

    if (high - low == 1) {
        if (arr[low] > arr[high]) {
            result.min = arr[high];
            result.max = arr[low];
        } else {
            result.min = arr[low];
            result.max = arr[high];
        }
        return result;
    }

    mid = low + (high - low) / 2;
    mml = find_min_max(arr, low, mid);
    mmr = find_min_max(arr, mid + 1, high);

    result.max = (mml.max >= mmr.max) ? mml.max : mmr.max;
    result.min = (mml.min <= mmr.min) ? mml.min : mmr.min;

    return result;
}

int main(void)
{
    int arr[] = {1000, 11, 445, 1, 330, 3000};
    int n = sizeof(arr) / sizeof(arr[0]);
    struct min_max printout;

    if (n == 0) {
        printf("Array is empty.\n");
        return 1;
    }

    printout = find_min_max(arr, 0, n - 1);

    printf("The max : %d\n", printout.max);
    printf("The min : %d\n", printout.min);

    return 0;
}