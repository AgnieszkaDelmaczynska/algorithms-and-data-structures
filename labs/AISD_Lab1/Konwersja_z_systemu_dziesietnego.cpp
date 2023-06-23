#include <iostream>
#include <math.h>
using namespace std;

int main()
{
	char znaki[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '\0' };
	char result = '\0';

	int n;
	scanf_s("%d", &n);											//cin >> n;

	int liczba_do_konwersji; // X
	int podstawa; // P

	for (int k = 0; k < n; k++)
	{		
		scanf_s("%d", &liczba_do_konwersji);					//cin >> liczba_do_konwersji;
		scanf_s("%d", &podstawa); 								//cin >> podstawa;
		int dlugosc_wyniku;

		if (podstawa == 1)
		{
			dlugosc_wyniku = liczba_do_konwersji * 1;
			for (int l = 0; l < dlugosc_wyniku; l++)
			{
				printf("1");									//cout << 1;
			}
			printf("\n");										//cout << endl;
		}	
		else
		{
			dlugosc_wyniku = (floor(log(liczba_do_konwersji) / log(podstawa)) + 1);	
			char* wynik = new char[dlugosc_wyniku];
			int i = 0;
			while (liczba_do_konwersji > 0)
			{
				result = znaki[(liczba_do_konwersji % podstawa)];
				wynik[i] = result;
				i++;
				liczba_do_konwersji = (liczba_do_konwersji / podstawa);
			}
			for (int j = dlugosc_wyniku - 1; j >= 0; j--)
			{
				printf("%c", wynik[j]);							//cout << wynik[j];
			}
			printf("\n");										//cout << endl;
			delete[] wynik;
		}
	}
	return 0;
}