#include <iostream>
#include <stdio.h>
using namespace std;

void swap(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void print_array(int arr[], int size)
{
    for (int i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

void selectionSort(int arr[], int n)
{
    int max_index;
    for (int i = n - 1; i > 0; i--)
    {
        max_index = i;
        for (int j = i - 1; j >= 0; j--)
            if (arr[j] >= arr[max_index])
                max_index = j;
        swap(&arr[i], &arr[max_index]);
        print_array(arr, n);
    }
}

int main()
{
    int how_many_numbers;
    while (cin >> how_many_numbers)
    {
        int* number_list;
        number_list = new int[how_many_numbers];
        for (int i = 0; i < how_many_numbers; i++)
            cin >> number_list[i];

        selectionSort(number_list, how_many_numbers);
        printf("\n");
        delete[]number_list;
    }
}