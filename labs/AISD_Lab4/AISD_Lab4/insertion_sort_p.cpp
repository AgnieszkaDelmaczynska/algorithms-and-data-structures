//
//  main.cpp
//  Zamiana
//
//  Created by Jakub Powierza on 19.05.2015.
//  Copyright (c) 2015 Jakub Powierza. All rights reserved.
//

#include <iostream>
#include <stdio.h>

int main(int argc, const char * argv[]) {
    int ilosc = 0;
    while (scanf_s("%d", &ilosc) != EOF) {
        int *liczby = new int[ilosc];
        for (int i = 0; i < ilosc; i++) {
            scanf_s("%d", &liczby[i]);
        }
        
        // Sortowanie
        for (int i = 1; i < ilosc; i++) {
            int x = liczby[i];
            int j = i-1;
            for (j = i-1; j >= 0; j--) {
                if (x >= liczby[j]) {
                    break;
                }
                liczby[j+1] = liczby[j];
            }
            liczby[j+1] = x;
            for (int t = 0; t < ilosc; t++) {
                printf("%d ", liczby[t]);
            }
            printf("\n");
        }

        printf("\n");
    }
    return 0;
}
