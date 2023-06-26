#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

enum {
    CMD_LENGTH,
    CMD_PRINT,
    CMD_ADD_ELEMENTS,
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
Elem* first, * last;


int parseEnum(char cmd) {
    return cmd == 'L' ? CMD_LENGTH :
        cmd == 'P' ? CMD_PRINT :
        cmd == 'E' ? CMD_ADD_ELEMENTS :
        CMD_ERROR;
}

Elem* search(int key)
{
    if (!first) return NULL;
    Elem* tmp = first;
    while (tmp->key != key && tmp != last) tmp = tmp->next;
    if (tmp->key == key) return tmp;
    else return NULL;
}

void printAll() {
    if (!first || isEmptyQueue) printf("-\n");
    else {
        Elem* tmp = first;
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
    Elem* tmp = first;
    while (tmp->next != first) { tmp = tmp->next; len++; }
    return len;
}

void add_to_list(int n)
{
    if (n == 0) return;
    Elem* temp = last;
    int beginning = 0;
    if (first == NULL)
    {
        temp = last = first = new Elem(NULL, 0);
        beginning = 1;
    }
    for (int i = beginning; i < n; i++)
    {
        Elem* new_node = new Elem(NULL, 0);
        temp->next = new_node;
        temp = new_node;
    }
    last = temp;
    temp->next = first;
}

void add_elements()
{
    int number;
    char symbol;
    while (scanf("%d%c", &number, &symbol))
    {
        if ((last != NULL) && (last->next != first) && (isEmptyQueue == false))
        {
            last->next->key = number;
            last = last->next;
        }
        else
        {
            add_to_list(1);
            last->key = number;
        }
        isEmptyQueue = false;
        if (symbol == '\n')
            break;
    }
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

        case CMD_ADD_ELEMENTS:
        {
            add_elements();
            break;
        }

        case CMD_ERROR:
        default:
            break;
        }
    }
    return 0;
}