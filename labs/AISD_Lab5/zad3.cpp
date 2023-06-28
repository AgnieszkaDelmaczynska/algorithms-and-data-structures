#include<stdio.h>
#include<iostream>
using namespace std;
bool czyLiczba(char x){
    if (x == 't') return true;
    if (x == 'f') return true;
    return false;
}

int waga(char x){
    switch (x) {
        case 'A':case 'K': return 1;
        case 'N':return 2;
        default:
            return 0;
    }
}

bool czyOperand(char x){
    return waga(x) > 0;
}

void zamianaONP(char * tab, int rozm){
    int itWyniku = 0;
    int ileNawiasow = 0;
    int itStosu = 0;
    char *stos = new char[rozm];
    cout << " b ";
    for (int j = 0; j < rozm; j++)
    {
        cout << " a ";
        if (czyLiczba(tab[j]))
            tab[itWyniku++] = tab[j];
        else if (tab[j] == '(')
            stos[itStosu++] = tab[j];
        else if (tab[j] == ')'){
            ileNawiasow++;
            while (stos[itStosu - 1] != '(')
            {
                tab[itWyniku++] = stos[--itStosu];
            }
            itStosu--;
        }
        else{
            while (itStosu>0 && stos[itStosu - 1] != '(' && waga(stos[itStosu - 1]) >= waga(tab[j]))
            {
                tab[itWyniku++] = stos[--itStosu];

            }
            stos[itStosu++] = tab[j];
        }
    }
    while (itStosu > 0){
        tab[itWyniku++] = stos[--itStosu];
    }
    tab[rozm - 2 * ileNawiasow] = '\0';
}

int wartosc(char x){
    if (x == 't') return 1;
    else return 0;
}

char znak(int x){
    if (x>0) return 't';
    return 'f';
}

char oblicz(int a, int b, char operand){
    switch (operand) {
        case 'K': return znak(a * b);
        case 'A': return znak(a + b);
    }
    return 0;
}

int wynikONP(char * tab, int rozm){
    int * struktura = new int[rozm];
    int itStosu = 0;
    for (int i = 0; tab[i] != '\0'; i++){
        if (czyLiczba(tab[i]))
            struktura[itStosu++] = tab[i];
        else if(tab[i]!='N'){
            int a = wartosc(struktura[--itStosu]), b = wartosc(struktura[--itStosu]);
            struktura[itStosu++] = oblicz(a, b, tab[i]);
        }
        else{
            struktura[itStosu - 1] = znak(((wartosc(struktura[itStosu - 1]) + 1) % 2));
        }
    }
    return struktura[0];
}

int main(){
    int n = 0;
    char tablica[400];
    scanf_s("%d\n", &n);
    for (int x = 0; x<n; x++){
        int i = -1;
        do{
            cin >> tablica[++i];
        } while (tablica[i] != '\n');
        zamianaONP(tablica, i);
        //printf("%s\n", tab);
        printf("%c\n", wynikONP(tablica, i));
    }
    
    return 0;
    
}