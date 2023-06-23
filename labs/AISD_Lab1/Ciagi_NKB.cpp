#include <iostream>
#include <stdio.h>
#include <math.h>
#define MAX_BIN_DIGITS 20 
using namespace std;
// check_binary_digits sprawdza ile pozycji potrzeba, aby zapisac liczbe w postaci binarnej
int check_binary_digits(int liczba, int first_digit, int last_digit, int digit_num)
{
    //printf("%d %d ,%d, %d \n", first_digit, last_digit, (first_digit + last_digit) / 2, digit_num);
    if (digit_num <= 1)
        return first_digit;
    int wartosc = pow(2, (first_digit + last_digit) / 2); // pow podnosi do potęgi, pierwszy argument to podstawa, drugi to wykładnik
    if (liczba == wartosc)
        return (first_digit + last_digit) / 2;
    else if (liczba >= wartosc)
        return check_binary_digits(liczba, (first_digit + last_digit) / 2 + 1, last_digit, digit_num / 2);
    else 
        return check_binary_digits(liczba, first_digit, (first_digit + last_digit) / 2 - 1, digit_num / 2);
}
int main()
{
    char tablica[MAX_BIN_DIGITS];
    int ile_liczb;
    scanf_s("%d", &ile_liczb);
    int binary_digits = check_binary_digits(ile_liczb, 0, MAX_BIN_DIGITS, MAX_BIN_DIGITS);
    if (ile_liczb - 1 > pow(2, binary_digits))
        binary_digits++;
    //printf("%d", binary_digits);

    for (int j = 0; j < ile_liczb; j++)
    {       
        bool poczatek = true;
        int liczba_temp = j;
        for (int k = 1; k <= binary_digits; k++)
        {
            if (liczba_temp < pow(2, binary_digits - k))
            {
                if (poczatek == true && k != binary_digits && ile_liczb != 1)printf(".");
                else printf("0");
            }
            else
            {
                printf("1");
                liczba_temp -= pow(2, binary_digits - k);
                poczatek = false;
            }
        }
        if (ile_liczb == 1)
            cout << 0;
        printf(" %d \n", j);
    }
    return 0;
}