// Badanie spójności grafu
// Data: 6.01.2014
// (C)2014 mgr Jerzy Wałaszek
//---------------------------

#include <iostream>

using namespace std;

// Typy dla dynamicznej tablicy list sąsiedztwa i stosu

struct slistEl
{
    slistEl* next;
    int v;
};

class stack
{
private:
    slistEl* S;   // lista przechowująca stos

public:
    stack();       // konstruktor
    ~stack();      // destruktor
    bool empty(void);
    int  top(void);
    void push(int v);
    void pop(void);
};

//---------------------
// Metody obiektu stack
//---------------------

// Konstruktor
//------------
stack::stack()
{
    S = NULL;
}

// Destruktor - zwalnia tablicę dynamiczną
//----------------------------------------
stack::~stack()
{
    while (S) pop();
}

// Sprawdza, czy stos jest pusty
//------------------------------
bool stack::empty(void)
{
    return !S;
}

// Zwraca szczyt stosu
//--------------------
int stack::top(void)
{
    return S->v;
}

// Zapisuje na stos
//-----------------
void stack::push(int v)
{
    slistEl* e = new slistEl;
    e->v = v;
    e->next = S;
    S = e;
}

// Usuwa ze stosu
//---------------
void stack::pop(void)
{
    if (S)
    {
        slistEl* e = S;
        S = S->next;
        delete e;
    }
}

// **********************
// *** PROGRAM GŁÓWNY ***
// **********************

int main()
{
    int n, m;       // Liczba wierzchołków i krawędzi
    slistEl** A;   // Tablica list sąsiedztwa grafu
    bool* visited; // Tablica odwiedzin
    stack S;        // Stos
    int i, v, u, vc;
    slistEl* p, * r;

    cin >> n >> m;           // Odczytujemy liczbę wierzchołków i krawędzi

    A = new slistEl * [n]; // Tworzymy tablice dynamiczne
    visited = new bool[n];

    // Inicjujemy tablice

    for (i = 0; i < n; i++)
    {
        A[i] = NULL;
        visited[i] = false;
    }

    // Odczytujemy kolejne definicje krawędzi.

    for (i = 0; i < m; i++)
    {
        cin >> v >> u;      // Wierzchołki tworzące krawędź
        p = new slistEl;    // Tworzymy nowy element
        p->v = u;           // Numerujemy go jako w
        p->next = A[v];  // Dodajemy go na początek listy A [ v ] 
        A[v] = p;
        p = new slistEl;    // To samo dla krawędzi w drugą stronę
        p->v = v;
        p->next = A[u];
        A[u] = p;
    }

    // Badamy spójność grafu

    vc = 0;               // Zerujemy licznik wierzchołków

    S.push(0);         // Wierzchołek startowy na stos
    visited[0] = true; // Oznaczamy go jako odwiedzony

    while (!S.empty())  // Wykonujemy przejście DFS
    {
        v = S.top();       // Pobieramy wierzchołek ze stosu
        S.pop();           // Pobrany wierzchołek usuwamy ze stosu
        vc++;               // Zwiększamy licznik wierzchołków
        for (p = A[v]; p; p = p->next) // Przeglądamy sąsiadów
        {
            u = p->v;
            if (!visited[u])    // Szukamy wierzchołków nieodwiedzonych
            {
                visited[u] = true; // Oznaczamy wierzchołek jako odwiedzony
                S.push(u);         // i umieszczamy go na stosie
            }
        }
    }

    // Wyświetlamy wyniki

    cout << endl;

    if (vc == n) cout << "CONNECTED GRAPH";
    else cout << "DISCONNECTED GRAPH";

    cout << endl;

    // Usuwamy tablice dynamiczne

    for (i = 0; i < n; i++)
    {
        p = A[i];
        while (p)
        {
            r = p;
            p = p->next;
            delete r;
        }
    }

    delete[] A;
    delete[] visited;

    return 0;
}