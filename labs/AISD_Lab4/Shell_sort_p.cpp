//
//  main.cpp
//  Zamiana
//
//  Created by Jakub Powierza on 19.05.2015.
//  Copyright (c) 2015 Jakub Powierza. All rights reserved.
//

#include <iostream>
#include <cmath>
#include <stdio.h>

int main(int argc, const char * argv[]) {
    int ilosc = 0;
    while (scanf_s("%d", &ilosc) != EOF) {
        int *liczby = new int[ilosc];
        for (int i = 0; i < ilosc; i++) {
            scanf_s("%d", &liczby[i]);
        }
        
        // Sortowanie
        int k = (1 << (int)(1.0f*log((double)ilosc+1.0f)/log(2.0f))) - 1;
        while (k >= 1) {
            for (int i = k; i < ilosc; i++) {
                int x = liczby[i];
                int j = i - k;
                while (j >= 0 && x < liczby[j]) {
                    liczby[j+k] = liczby[j];
                    j = j - k;
                }
                liczby[j+k] = x;
            }
            k = (k+1)/2 - 1;
            for (int i = 0; i < ilosc; i++) {
                printf("%d ", liczby[i]);
            }
            printf("\n");
        }
        
        printf("\n");
    }
    return 0;
}
