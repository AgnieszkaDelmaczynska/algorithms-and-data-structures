#include <iostream>
#include <cmath>
using namespace std;

int ile_miejsc(int liczba_do_konwersji, int podstawa)
{
	int x;
	x = (floor(log(liczba_do_konwersji) / log(podstawa)) + 1);
	return x;
}

int main()
{
	char znaki[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '\0' };
	char result = '\0';

	int n;
	cin >> n;

	int liczba_do_konwersji; // X
	int podstawa = 2; // P

	for (int k = 0; k < n; k++)
	{
		liczba_do_konwersji = k;
		int i = 0;
		int dlugosc_wyniku;

		if (liczba_do_konwersji == 0)
		{
			cout << "0 0" << endl;
		}
		else
		{
			dlugosc_wyniku = (floor(log(liczba_do_konwersji) / log(podstawa)) + 1);
			char* wynik = new char[dlugosc_wyniku];

			while (liczba_do_konwersji > 0)
			{
				result = znaki[(liczba_do_konwersji % podstawa)];
				wynik[i] = result;
				i++;
				liczba_do_konwersji = (liczba_do_konwersji / podstawa);
			}
			for (int j = dlugosc_wyniku - 1; j >= 0; j--)
			{
				cout << wynik[j];
			}
			cout << " " << k << endl;
			delete[] wynik;	
		}
	}
	system("pause");
	return 0;
}