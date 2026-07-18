#include <iostream>
#include <utility>
#include <vector>

int partitionRange(std::vector<int>& values, int low, int high)
{
    int pivot = values[high];
    int smallerIndex = low - 1;

    for (int current = low; current < high; ++current)
    {
        if (values[current] <= pivot)
        {
            ++smallerIndex;
            std::swap(values[smallerIndex], values[current]);
        }
    }

    std::swap(values[smallerIndex + 1], values[high]);
    return smallerIndex + 1;
}

void quickSort(std::vector<int>& values, int low, int high)
{
    if (low < high)
    {
        int pivotIndex = partitionRange(values, low, high);

        quickSort(values, low, pivotIndex - 1);
        quickSort(values, pivotIndex + 1, high);
    }
}

int main()
{
    int n;

    std::cout << "Enter number of elements: ";
    if (!(std::cin >> n) || n < 0)
    {
        return 0;
    }

    std::vector<int> values(n);

    std::cout << "Enter elements:\n";
    for (int i = 0; i < n; ++i)
    {
        if (!(std::cin >> values[i]))
        {
            return 0;
        }
    }

    if (n > 0)
    {
        quickSort(values, 0, n - 1);
    }

    std::cout << "\nSorted array:\n";
    for (int i = 0; i < n; ++i)
    {
        std::cout << values[i] << ' ';
    }
    std::cout << '\n';

    return 0;
}