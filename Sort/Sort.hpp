#ifndef SORT
#define SORT
#include <cmath>
template <typename elemType>
class Sort
{
private:
    static void QuickSort(elemType a[], int low, int high);
    static int Division(elemType a[], int low, int high);
    static void BuildHeap(elemType a[], int size);
    static elemType deQueue(elemType a[], int size);
    static void percolateDown(elemType a[], int size, int hole);

public:
    static void InsertionSort(elemType a[], int size); // O(N^2)
    static void ShellSort(elemType a[], int size);     // Really fast!

    static void SelectionSort(elemType a[], int size); // O(N^2)
    static void HeapSort(elemType a[], int size);      // O(N*logN)

    static void BubbleSort(elemType a[], int size); // O(N^2)
    static void QuickSort(elemType a[], int size);  // O(N*logN) ~ O(N^2)

    static void MergeSort(elemType a[], int size);

    static void BucketSort(elemType a[], int size);
    static void CountingSort(elemType a[], int size);
    static void RandixSort(elemType a[], int size);
};

template <typename elemType>
void Sort<elemType>::InsertionSort(elemType a[], int size)
{
    int j;
    elemType tmp;
    for (int i = 1; i < size; ++i)
    {
        tmp = a[i];
        for (j = i; a[j - 1] > tmp && j > 0; --j)
            a[j] = a[j - 1];
        a[j] = tmp;
    }
}

template <typename elemType>
void Sort<elemType>::ShellSort(elemType a[], int size)
{
    int gap = size;
    int time = 1;
    int tmp;
    int j;
    while (gap > 1)
    {
        gap = size / std::pow(2, time);
        time++;
        gap = (gap % 2 == 0) ? gap - 1 : gap;
        for (int i = gap; i < size; i++)
        {
            tmp = a[i];
            for (j = i; j - gap >= 0 && a[j - gap] > a[j]; j -= gap)
                a[j] = a[j - gap];
            a[j] = tmp;
        }
    }
}

template <typename elemType>
void Sort<elemType>::SelectionSort(elemType a[], int size)
{
    int pos;
    for (int i = 0; i < size; i++)
    {
        pos = i;
        for (int j = i; j < size; j++)
        {
            if (a[j] < a[pos])
                pos = j;
        }
        std::swap(a[i], a[pos]);
    }
}

template <typename elemType>
void Sort<elemType>::BubbleSort(elemType a[], int size)
{
    int j;
    elemType tmp;
    bool flag = true;
    for (int i = 1; i < size && flag; i++)
    {
        flag = false;
        j = 0;
        while (j < size - i)
        {
            tmp = a[j];
            for (; a[j + 1] < tmp && j < size - i; j++)
            {
                a[j] = a[j + 1];
                flag = true;
            }
            a[j] = tmp;
            j++;
        }
    }

    // int i, j;
    // bool flag = true;
    // for (i = 1; i < size && flag; ++i)
    // {
    //     flag = false;
    //     for (j = 0; j < size - i; ++j)
    //         if (a[j + 1] < a[j])
    //         {
    //             std::swap(a[j], a[j + 1]);
    //             flag = true;
    //         }
    // }
}

template <typename elemType>
void Sort<elemType>::QuickSort(elemType a[], int size)
{
    QuickSort(a, 0, size - 1);
}

template <typename elemType>
void Sort<elemType>::QuickSort(elemType a[], int low, int high)
{
    if (low >= high)
        return;
    int mid = Division(a, low, high);
    QuickSort(a, mid + 1, high);
    QuickSort(a, low, mid - 1);
}

template <typename elemType>
int Sort<elemType>::Division(elemType a[], int low, int high)
{
    elemType key = a[low];
    while (low < high)
    {
        while (low < high && a[high] >= key)
            high--;
        a[low] = a[high];

        while (low < high && a[low] <= key)
            low++;
        a[high] = a[low];
    }
    a[low] = key;
    return low;
}
template <typename elemType>
void Sort<elemType>::HeapSort(elemType a[], int size)
{
    elemType tmp;
    BuildHeap(a, size);
    for (int i = 0; i < size; i++)
    {
        tmp = deQueue(a, size - i);
        a[size - i - 1] = tmp;
    }
}
template <typename elemType>
void Sort<elemType>::BuildHeap(elemType a[], int size)
{
    for (int i = (size + 1) / 2 - 1; i >= 0; i--)
        percolateDown(a, size, i);
}
template <typename elemType>
elemType Sort<elemType>::deQueue(elemType a[], int size)
{
    elemType tmp = a[0];
    a[0] = a[size - 1];
    percolateDown(a, size - 1, 0);
    return tmp;
}
template <typename elemType>
void Sort<elemType>::percolateDown(elemType a[], int size, int hole)
{
    elemType key = a[hole];
    int child = (hole + 1) * 2 - 1;
    while (child <= size - 1)
    {
        if (child != size - 1 && a[child] < a[child + 1])
            child++;
        if (key < a[child])
        {
            a[hole] = a[child];
            hole = child;
            child = (hole + 1) * 2 - 1;
        }
        else
            break;
    }
    a[hole] = key;
}

#endif