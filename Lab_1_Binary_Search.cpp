#include <cstdio>

constexpr int MAX_SIZE = 50;

int binarySearch(const int arr[], int n, int target)
{
    int low = 0;
    int high = n - 1;

    while (low <= high)
    {
        int mid = low + (high - low) / 2;

        if (arr[mid] == target)
        {
            return mid;
        }
        if (arr[mid] < target)
        {
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }

    return -1;
}

int readInt(const char *prompt)
{
    int value;
    printf("%s", prompt);
    scanf("%d", &value);
    return value;
}

void readArray(int arr[], int n)
{
    printf("Enter elements in sorted order:\n");
    for (int i = 0; i < n; ++i)
    {
        scanf("%d", &arr[i]);
    }
}

int main()
{
    int arr[MAX_SIZE];

    int n = readInt("Enter number of elements (must be sorted): ");
    readArray(arr, n);

    int target = readInt("Enter target element to search: ");
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