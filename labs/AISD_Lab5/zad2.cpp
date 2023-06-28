#include <iostream>
#include <stdio.h>

using namespace std;

enum typ{
    N = 1,
    K = 2,
    A = 3,
    T = 4,
    F = 5
};

class elem {
public:
    typ t;
    bool op;
    bool wyr;
    elem* next;
    elem* prev;
    
    elem(typ typ){
        this->dl = 1;
        this->t = typ;
        this->wyr = false;
        this->wyrazenie = NULL;
        this->next = NULL;
        this->prev = NULL;
        if(typ ==T || typ == F){
            this->op = false;
        }else{
            this->op = true;
        }
    }
    int dl;
    char* wyrazenie;
    elem(typ typOperator, typ typA, typ typB){
        this->dl = 1;
        this->wyr = false;
        this->wyrazenie = NULL;
        this->next = NULL;
        this->prev = NULL;
        this->op = false;
        if(typOperator ==K){
            bool a = (typA==T);
            bool b = (typB==T);
            if(a && b){
                this->t = T;
            }else {
                this->t = F;
            }
        }else if(typOperator == A){
            bool a = (typA==T);
            bool b = (typB==T);
            if(a || b){
                this->t = T;
            }else {
                this->t = F;
            }
        }else if(typOperator == N){
            if(typA == T){
                this->t = F;
            }else if(typA == F){
                this->t = T;
            }
        }
    }
    
    elem(char operatorX, char* wyrazenieA, int dlA, char* wyrazenieB, int dlB){
        this->dl = (dlA+dlB+3);
        this->wyr = true;
        this->prev = this->next = NULL;
        this->wyrazenie = (char*)malloc(sizeof(char)*(dl+1));
        int i=0;
        wyrazenie[i++] = '(';
        for(; (i-1)<dlA; i++){
            wyrazenie[i] = wyrazenieA[i-1];
        }
        wyrazenie[i++] = operatorX;
        int j=0;
        for(; j<dlB; i++){
            wyrazenie[i] = wyrazenieB[j++];
        }
        wyrazenie[i++] = ')';
        wyrazenie[i++] = '\0';
    }
    
    //char* wezWyrazenie()
    //{
    //    if(this->wyr)
    //    {
    //        return wyrazenie;
    //    }
    //    else if(this->t==T)
    //    {
    //        return "t";
    //    }
    //    else if(this->t==F)
    //    {
    //        return "f";
    //    }
    //    return NULL;
    //}
};

typ okreslTyp(char c){
    if(c=='K'){
        return K;
    }else if(c=='N'){
        return N;
    }else if(c=='A'){
        return A;
    }else if(c=='t'){
        return T;
    }else if(c=='f'){
        return F;
    }
    return T;
}

int getInputSize(){
    int iloscLinii = 0;
    
    scanf_s("%d\n",&iloscLinii);
    return iloscLinii;
}

elem* getElement(){
    char jedenZnak;
    scanf_s("%c",&jedenZnak);
    elem* element = new elem(okreslTyp(jedenZnak));
    return element;
}

bool wartosc(typ typ, bool x1, bool x2){
    if(typ == K){
        return (x1 && x2);
    }else if(typ == A){
        return (x1 || x2);
    }else if(typ == N){
        return !x1;
    }
    return false;
}

bool rekurencja(elem* element ){
    elem* element1  = getElement();
    bool wartosc1 = false;
    bool wartosc2 = false;
    if(element1->op){
        wartosc1 = rekurencja(element1);
    }else{
        wartosc1 = element1->t==T;
    }
    if(element->t!= N){
        elem* element2  = getElement();
        if(element2->op){
            wartosc2 = rekurencja(element2);
        }else{
            wartosc2 = element2->t==T;
        }
    }
    return wartosc(element->t, wartosc1, wartosc2);
}

int notacjaONP(){
    char jedenZnak;
    int iloscLinii = getInputSize();
    for(int i=0; i<iloscLinii;i++){
        scanf_s("%c",&jedenZnak);
        elem* element = new elem(okreslTyp(jedenZnak));
        if(rekurencja(element)){
            printf("t\n");
        }else{
            printf("f\n");
        }
        scanf_s("%c",&jedenZnak);
    }
    return 0;
}


int main(){
    int response =1;
    while (response >0){
        response = notacjaONP();
    }
    
    return 0;
}