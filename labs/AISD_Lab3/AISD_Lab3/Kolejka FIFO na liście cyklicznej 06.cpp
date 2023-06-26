#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

enum {
    CMD_LENGTH,
    CMD_PRINT,
    CMD_ADD,
    CMD_ADD_ELEMENTS,
    CMD_DISPLAY,
    CMD_ERROR
} ecmd;

struct Elem {
    int key;
    Elem* next;
    Elem(Elem* e, int k) : next(e), key(k) { }
};

char cmd;
int n;
bool isEmptyQueue;
Elem *first, *last;


int parseEnum(char cmd) {
    return cmd == 'L' ? CMD_LENGTH :
    cmd == 'P' ? CMD_PRINT :
    cmd == 'C' ? CMD_ADD :
    cmd == 'E' ? CMD_ADD_ELEMENTS :
    cmd == 'D' ? CMD_DISPLAY :
    CMD_ERROR;
}

Elem *search(int key)
{
    if (!first) return NULL;
    Elem *tmp = first;
    while (tmp->key != key && tmp != last) tmp = tmp->next;
    if (tmp->key == key) return tmp;
    else return NULL;
}

void printAll() {
    if (!first || isEmptyQueue) printf("-\n");
    else {
        Elem *tmp = first;
        while (tmp != last) {
            printf("%d->", tmp->key);
            tmp = tmp->next;
        }
        printf("%d\n", last->key);
    }
}

int totalLength()
{
    if (!first) return 0;
    int len(1);
    Elem *tmp = first;
    while (tmp->next != first) { tmp = tmp->next; len++; }
    return len;
}

// Zadanie 1
void add(int n) {
    if (n == 0) return;
    isEmptyQueue = false;
    Elem* tmp = last;
    int start = 0;
    if (first == NULL) {
        tmp = first = last = new Elem(NULL, 0);
        start = 1;
    }
    for (int i = start; i < n; i++) {
        Elem* t = new Elem(NULL, 0);
        tmp->next = t;
        tmp = t;
    }
    tmp->next = first;
    last = tmp;
}

// Zadanie 2

// Zadanie 3
void display(int n) {
    for (int i = 0; i < n; i++) {
        if (isEmptyQueue) {
            printf("- ");
        }
        else {
            if (first == last) {
                printf("%d ", first->key);
                first = first->next;
                isEmptyQueue = true;
            } else {
                printf("%d ", first->key);
                first = first->next;
            }
        }
    }
    printf("\n");
}

int main()
{
    isEmptyQueue = true;
    while (scanf("%c", &cmd) > 0) {
        switch (parseEnum(cmd))
        {
            case CMD_LENGTH:
                printf("%d\n", totalLength());
                break;
                
            case CMD_PRINT:
                printAll();
                break;
                
            case CMD_ADD: {
                int n;
                scanf_s("%d", &n);
                add(n);
                break;
            }
                
            case CMD_ADD_ELEMENTS: {
                int liczba;
                char znak;
                while (scanf_s("%d%c", &liczba, &znak)) {
                    if (last != NULL && isEmptyQueue == false && last->next != first) {
                        last->next->key = liczba;
                        last = last->next;
                    } else {
                        add(1);
                        last->key = liczba;
                    }
                    isEmptyQueue = false;
                    if (znak == '\n') break;
                }
                break;
            }
                
            case CMD_DISPLAY: {
                int liczba;
                scanf_s("%d", &liczba);
                display(liczba);
                break;
            }
                
            case CMD_ERROR:
            default:
                break;
        }
        
    }
    return 0;
}
