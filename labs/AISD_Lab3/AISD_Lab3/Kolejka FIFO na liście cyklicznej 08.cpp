#include <stdio.h>


enum {
    CMD_LENGTH,
    CMD_PRINT,
    CMD_ADD,
    CMD_ADD_ELEMENTS,
    CMD_DISPLAY,
    CMD_REMOVE,
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
    cmd == 'R' ? CMD_REMOVE :
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
    if (n <= 0) return;
    for (int i = 0; i < n; i++) {
        if (isEmptyQueue) {
            printf("- ");
        }
        else {
            printf("%d ", first->key);
            if (first == last) {
                isEmptyQueue = true;
            } else {
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
                scanf("%d", &n);
                add(n);
                break;
            }
                
            case CMD_ADD_ELEMENTS: {
                int liczba;
                char znak;
                while (scanf("%d%c", &liczba, &znak)) {
                    if (first != NULL && last != NULL && first == last && isEmptyQueue) {
                        first->key = liczba;
                        isEmptyQueue = false;
                    } else {
                        if (first != NULL && last != NULL) {
                            if (last->next == first) {
                                add(1);
                            } else {
                                last = last->next;
                            }
                        } else {
                            add(1);
                        }
                        last->key = liczba;
                    }
                    isEmptyQueue = false;
                    if (znak == '\n') break;
                }
                break;
            }
                
            case CMD_DISPLAY: {
                int liczba;
                scanf("%d", &liczba);
                display(liczba);
                break;
            }
                
            case CMD_REMOVE: {
                int liczba;
                scanf("%d", &liczba);
                if (first != NULL) {
                    Elem *before = first;
                    Elem *tmp = first;
                    while (tmp->key != liczba && tmp != last) {
                        before = tmp;
                        tmp = tmp->next;
                    }
                    if (tmp->key == liczba) {
                        before->next = tmp->next;
                        if (tmp == first && first == last) {
                            first = NULL;
                            last = NULL;
                            isEmptyQueue = true;
                        } else if (tmp == first) {
                            first = first->next;
                            last->next = first;
                        } else if (tmp == last) {
                            last = before;
                        }
                        delete tmp;
                    }
                }
                break;
            }
                
            case CMD_ERROR:
            default:
                break;
        }
        
    }
    return 0;
}
