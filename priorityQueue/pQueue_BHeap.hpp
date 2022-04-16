#ifndef CLASS_PRIORITYQUEUE_B
#define CLASS_PRIORITYQUEUE_B
//这里考虑越小的优先级越高

template <typename elemType>
class priorityQueue
{
private:
    elemType *array;
    int maxSize;
    int currentSize;
    void doubleSpace();
    void percolateDown(int hole);
    void percolateDown(int hole, elemType temp);
    void buildHeap(int i);
    void buildHeap();

public:
    priorityQueue();
    priorityQueue(elemType *input, int size);
    ~priorityQueue();
    elemType getHead() const;
    bool isEmpty() const;
    elemType deQueue();
    void enQueue(const elemType &x);
};

template <typename elemType>
priorityQueue<elemType>::priorityQueue()
{
    maxSize = 5;
    currentSize = 0;
    array = new elemType[maxSize];
}

template <typename elemType>
priorityQueue<elemType>::priorityQueue(elemType *input, int size)
{
    maxSize = size * 2;
    currentSize = size;
    array = new elemType[maxSize];
    for (int i = 0; i < size; i++)
    {
        array[i + 1] = input[i];
    }
    buildHeap();
    // buildHeap(1);
}

template <typename elemType>
priorityQueue<elemType>::~priorityQueue()
{
    delete[] array;
}

template <typename elemType>
bool priorityQueue<elemType>::isEmpty() const
{
    return !currentSize;
}

template <typename elemType>
elemType priorityQueue<elemType>::getHead() const
{
    return array[1];
}

template <typename elemType>
elemType priorityQueue<elemType>::deQueue()
{
    int hole = 1;
    elemType head = array[1];
    array[hole] = array[currentSize--];
    percolateDown(hole, array[hole]);
    return head;
}

template <typename elemType>
void priorityQueue<elemType>::enQueue(const elemType &x)
{
    if (currentSize == maxSize - 1)
        doubleSpace();
    int hole = ++currentSize;
    while (hole > 1 && x < array[hole / 2])
    {
        array[hole] = array[hole / 2];
        hole /= 2;
    }
    array[hole] = x;
}

// recursive version
template <typename elemType>
void priorityQueue<elemType>::percolateDown(int hole, elemType temp)
{
    array[0] = temp;
    if (hole * 2 > currentSize)
    {
        array[hole] = array[0];
        return;
    }

    if (hole * 2 == currentSize)
    {
        if (array[0] <= array[hole * 2])
        {
            array[hole] = array[0];
            return;
        }
        else
        {
            array[hole] = array[2 * hole];
            percolateDown(hole * 2, temp);
        }
    }
    else
    {
        if (array[0] <= array[hole * 2] && array[0] <= array[hole * 2 + 1])
        {
            array[hole] = array[0];
            return;
        }
        else if (array[hole * 2] < array[hole * 2 + 1])
        {
            array[hole] = array[2 * hole];
            percolateDown(hole * 2, temp);
        }
        else
        {
            array[hole] = array[2 * hole + 1];
            percolateDown(hole * 2 + 1, temp);
        }
    }
}

// iterative version
template <typename elemType>
void priorityQueue<elemType>::percolateDown(int hole)
{
    int child;
    array[0] = array[hole];
    while (hole * 2 <= currentSize)
    {
        child = hole * 2;
        if (child < currentSize && array[child] > array[child + 1])
            child++;
        if (array[0] > array[child])
        {
            array[hole] = array[child];
            hole = child;
        }
        else
            break;
    }
    array[hole] = array[0];
}

// recursive version
template <typename elemType>
void priorityQueue<elemType>::buildHeap(int i)
{
    if (i * 2 > currentSize)
        return;
    if (i * 2 == currentSize)
        percolateDown(i);
    buildHeap(i * 2);
    buildHeap(i * 2 + 1);
    percolateDown(i);
}

// iterative version
template <typename elemType>
void priorityQueue<elemType>::buildHeap()
{
    int pos = currentSize / 2;
    while (pos >= 1)
    {
        percolateDown(pos);
        pos--;
    }
}

template <typename elemType>
void priorityQueue<elemType>::doubleSpace()
{
    maxSize *= 2;
    elemType *temp = new elemType[maxSize];
    for (int i = 1; i <= currentSize; i++)
    {
        temp[i] = array[i];
    }
    delete[] array;
    array = temp;
}
#endif