#include <iostream>
#include <stdio.h>
using namespace std;
using type_bool = bool;
using type_void = void;
#define NATURAL_NUMBER_WHICH_NAME_IN_ENGLISH_IS_ONE_NOT_ZERO 1
#define NUMBER_ZERO 0
type_void swap_elements_in_table(int* tab, int a, int b)
{
	int temp = tab[a];
	tab[a] = tab[b];
	tab[b] = temp;
}
type_bool zero_requirement(int* tab, int how_many_zeros, int size_of_tab)
{
	type_bool requirement = false;
	for (int i = NATURAL_NUMBER_WHICH_NAME_IN_ENGLISH_IS_ONE_NOT_ZERO; i <= how_many_zeros; i++)
	{
		if (tab[size_of_tab - i] == NUMBER_ZERO)
			requirement = true;
		else
		{
			requirement = false;
			break;
		}
	}
	return requirement;
}
type_void print_table(int* tab, int size_of_tab)
{
	for (int i = NUMBER_ZERO; i < size_of_tab; i++)
		printf("%d", tab[i]);
	printf("\n");
}
int main()
{
	int pivot_element = NUMBER_ZERO;
	int size;
	int how_many_zeros = NUMBER_ZERO;
	scanf_s("%d", &size);

	int* table = new int[size];
	// create table
	for (int j = NUMBER_ZERO; j < size; j++)
	{
		table[j] = NATURAL_NUMBER_WHICH_NAME_IN_ENGLISH_IS_ONE_NOT_ZERO;
	}
	print_table(table, size);
	int i = NUMBER_ZERO;
	while (how_many_zeros != size)
	{
		if (how_many_zeros == NUMBER_ZERO)
		{
			table[NUMBER_ZERO] = NUMBER_ZERO;
			print_table(table, size);
			how_many_zeros++;
			continue;
			break;// nie trzeba
		}
		if (zero_requirement(table, how_many_zeros, size))
		{
			how_many_zeros++;
			i = NUMBER_ZERO;
			for (int j = NUMBER_ZERO; j < size; j++)
			{
				table[j] = NATURAL_NUMBER_WHICH_NAME_IN_ENGLISH_IS_ONE_NOT_ZERO;
			}
			for (int j = NUMBER_ZERO; j < how_many_zeros; j++)
				table[j] = NUMBER_ZERO;
			print_table(table, size);
			continue;
			break;// nie trzeba
		}
		if ((table[i] == NUMBER_ZERO) && (i != size - NATURAL_NUMBER_WHICH_NAME_IN_ENGLISH_IS_ONE_NOT_ZERO))
		{
			if (table[i + NATURAL_NUMBER_WHICH_NAME_IN_ENGLISH_IS_ONE_NOT_ZERO] == NATURAL_NUMBER_WHICH_NAME_IN_ENGLISH_IS_ONE_NOT_ZERO)
			{
				swap_elements_in_table(table, i, i + NATURAL_NUMBER_WHICH_NAME_IN_ENGLISH_IS_ONE_NOT_ZERO);
				pivot_element = NUMBER_ZERO;
				i = NUMBER_ZERO;
				print_table(table, size);
				continue;
				break;// nie trzeba
			}
			else
			{
				if (table[pivot_element] != NUMBER_ZERO)
				{
					swap_elements_in_table(table, i, pivot_element);
					pivot_element++;
				}
			}
		}
		i++;
	}
	return NUMBER_ZERO;
}