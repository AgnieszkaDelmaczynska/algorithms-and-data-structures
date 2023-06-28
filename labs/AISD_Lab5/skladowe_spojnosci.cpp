//
//  main.cpp
//  Spójność grafu
//
//  Created by Jakub Powierza on 08.06.2015.
//  Copyright (c) 2015 Jakub Powierza. All rights reserved.
//

#include <iostream>
#include <stdio.h>

// Element listy
struct ElementListy {
    // Dane
    int wartosc;
    ElementListy* nastepny;
    
    // Konstruktor elementu listy z wartością
    ElementListy(int w) {
        wartosc = w;
        nastepny = NULL;
    }
};

// Struktura listy
struct Lista {
    // Dane
    ElementListy* poczatek;
    ElementListy* koniec;
    
    // Funkcja dodająca elemety do listy
    void dodaj(int wartosc) {
        ElementListy* nowy = new ElementListy(wartosc);
        if (koniec) {
            koniec->nastepny = nowy;
            koniec = nowy;
        } else {
            poczatek = nowy;
            koniec = nowy;
        }
    }
};

// Struktura stosu
struct Stos {
    // Dane
    int ilosc;
    int dane[5000];
    
    // Dodanie elementu do stosu
    void dodaj(int wartosc) {
        dane[ilosc++] = wartosc;
    }
    
    // Pobranie elementu ze stosu
    int pobierz() {
        return dane[--ilosc];
    }
};

int main(int argc, const char * argv[]) {
    // Dane
    int t = 0;
    scanf_s("%d", &t);
    
    // Pętla główna
    while (t--) {
        // Dane
        int n = 0;
        scanf_s("%d", &n);
        
        // Graf
        Lista** graf = new Lista*[n];
        for (int i = 0; i < n; i++) {
            graf[i] = new Lista();
        }
        
        // Wczytywanie grafu
        for (int i = 0; i < n; i++) {
            int stopien;
            scanf_s("%d", &stopien);
            for (int p = 0; p < stopien; p++) {
                int a;
                scanf_s("%d", &a);
                graf[i]->dodaj(a);
            }
        }
        
        // Tablica składowych spójności
        int* skladoweSpojnosci = new int[n];
        for (int i = 0; i < n; i++) {
            skladoweSpojnosci[i] = 0;
        }
        
        // Stos trzymajacy dane o przetwarzanych wierzcholkach
        Stos stos;
        
        // Wyliczanie składowych spójności
        int skladowa = 0;
        for (int i = 0; i < n; i++) {
            if (skladoweSpojnosci[i] == 0) {
                // Zwiększenie ilości składowych
                skladowa++;
                
                // Dodanie wierzchołka startowego
                stos.dodaj(i);
                
                // Przechodzenie po sąsiadach, dopóki stos nie jest pusty
                while (stos.ilosc != 0) {
                    // Pobranie wierzchołka ze stosu
                    int wierzcholek = stos.pobierz();
                    
                    // Oznaczenie składowej dla danego wierzchołka
                    skladoweSpojnosci[wierzcholek] = skladowa;
                    
                    // Dodanie wszystkich, nieodwiedzonych sąsiadów do stosu
                    ElementListy* lista = graf[wierzcholek]->poczatek;
                    while (lista) {
                        if (skladoweSpojnosci[lista->wartosc] == 0)
                            stos.dodaj(lista->wartosc);
                        lista = lista->nastepny;
                    }
                }
            }
        }
        
        // Wypisanie wyniku
        printf("%d\n", skladowa);
    }
    return 0;
}
