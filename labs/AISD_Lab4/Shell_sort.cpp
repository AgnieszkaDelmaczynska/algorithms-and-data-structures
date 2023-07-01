#include <iostream>
#include <string>
#define EQUAL 0
#define FIRST 1
#define SECOND 0
using namespace std;
int compare_int(int a, int b)
{
    if (a > b) return FIRST;
    if (b > a) return SECOND;
    if (a == b) return EQUAL;
    return 0;
}
void shell_sort(int number_list[], int how_many_numbers)
{
    int first_to_compare;
    int second_to_compare_pos;
    int number_gap = (1 << (int)(1.0f * log((double)how_many_numbers + 1.0f) / log(2.0f))) - 1;
   // int number_gap = how_many_numbers / 2;
    while (number_gap >= 1)
    {
        for (int y = how_many_numbers - number_gap - 1; y >= 0; y--)
        {
            first_to_compare = number_list[y];
            second_to_compare_pos = y + number_gap;
            while (second_to_compare_pos < how_many_numbers && compare_int(first_to_compare, number_list[second_to_compare_pos]))
            {
                number_list[second_to_compare_pos - number_gap] = number_list[second_to_compare_pos];
                second_to_compare_pos += number_gap;
            }
            number_list[second_to_compare_pos - number_gap] = first_to_compare;
        }
        //number_gap /= 2;
        number_gap = (number_gap + 1) / 2 - 1;
        for (int i = 0; i < how_many_numbers; i++)
            cout << number_list[i] << " ";
        cout << endl;
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
        shell_sort(number_list, how_many_numbers);
        cout << endl;
        delete[]number_list;
    }
}