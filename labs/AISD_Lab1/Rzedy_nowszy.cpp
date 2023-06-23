#include <iostream>
#include <cmath>
#include <stdio.h>
using type = unsigned long long int;
using namespace std;

type row(type num, type order_of_magnitude)
{
	if (num < 10)
		return order_of_magnitude;
	else
	{
		num = num / 10;
		order_of_magnitude++;
		return row(num, order_of_magnitude);
	}
}

void swap(type* a, type* b)
{
	type t = *a;
	*a = *b;
	*b = t;
}

void bubble_sort(type** tab, type n)
{
	type i, j;
	bool swapped;
	for (i = 0; i < n - 1; i++)
	{
		swapped = false;
		for (j = 0; j < n - i - 1; j++)
		{
			if (tab[j][0] > tab[j + 1][0])
			{
				swap(&tab[j][1], &tab[j + 1][1]);
				swap(&tab[j][0], &tab[j + 1][0]);
				swapped = true;
			}
		}
		// If no two elements were swapped by inner loop, then break 
		if (swapped == false)
			break;
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	type number_of_rows = 0;
	cin >> number_of_rows;
	for (type i = 0; i < number_of_rows; i++)
	{
		type how_many_numbers_in_a_row;
		cin >> how_many_numbers_in_a_row;

		type** table_of_numbers = new type * [how_many_numbers_in_a_row];
		for (type i = 0; i < how_many_numbers_in_a_row; i++)
		{
			table_of_numbers[i] = new type[2];
		}

		for (type i = 0; i < how_many_numbers_in_a_row; i++)
		{
			type number;
			cin >> number;
			table_of_numbers[i][1] = number;										// na [i][1] number, na [i][0] row
			table_of_numbers[i][0] = row(table_of_numbers[i][1], 0);
		}
		bubble_sort(table_of_numbers, how_many_numbers_in_a_row);
		for (type i = 0; i < how_many_numbers_in_a_row; i++)
		{
			cout << table_of_numbers[i][1] << " "; // number
		}
		printf("\n");
	}
	return 0;
}