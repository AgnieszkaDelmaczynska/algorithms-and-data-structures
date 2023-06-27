#include <iostream>
using namespace std;

void heapify(int table[], int actual, int array_size)
{
    int left = actual * 2;
    int right = actual * 2 + 1;
    int maxpos;
    if (left <= array_size && table[left - 1] > table[actual - 1])
        maxpos = left;
    else maxpos = actual;
    if (right <= array_size && table[right - 1] > table[maxpos - 1])
        maxpos = right;
    if (maxpos != actual)
    {
        int temp = table[actual - 1];
        table[actual - 1] = table[maxpos - 1];
        table[maxpos - 1] = temp;
        heapify(table, maxpos, array_size);
    }
}
void build_heap(int table[], int array_size)
{
    for (int i = array_size / 2; i > 0; i--)
    {
        heapify(table, i, array_size);
        for (int a = 0; a < array_size; a++)
            cout << table[a] << " ";
        printf("\n");
    }
}

int main()
{
    int how_many_elements;
    while (cin >> how_many_elements)
    {
        int* heap = new int[how_many_elements];
        for (int i = 0; i < how_many_elements; i++)
            cin >> heap[i];
        build_heap(heap, how_many_elements);
        delete[]heap;
    }
}