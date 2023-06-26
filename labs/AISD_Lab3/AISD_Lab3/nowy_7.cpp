#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>


enum {
    CMD_LENGTH,
    CMD_PRINT,
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
Elem* first, * last;


int parseEnum(char cmd) {
    return cmd == 'L' ? CMD_LENGTH :
        cmd == 'P' ? CMD_PRINT :
        cmd == 'E' ? CMD_ADD_ELEMENTS :
        cmd == 'D' ? CMD_DISPLAY :
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

void remove_and_display(int n)
{
    if (n <= 0) return;
    for (int i = 0; i < n; i++)
    {
        if (isEmptyQueue == true) printf("- ");
        else
        {
            printf("%d ", first->key);
            if (first != last)
                first = first->next;
            else
                isEmptyQueue = true;
        }
    }
    printf("\n");
}

void add_elements()
{
    int number;
    char sign;
    while (scanf("%d%c", &number, &sign))
    {
        if ((first != NULL) && (first == last) && (last != NULL) && isEmptyQueue)
        {
            first->key = number;
            isEmptyQueue = false;
        }
        else
        {
            if (first != NULL && last != NULL)
            {
                if (last->next == first)
                    add_to_list(1);
                else
                    last = last->next;
            }
            else
                add_to_list(1);
            last->key = number;
        }
        isEmptyQueue = false;
        if (sign == '\n')
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

        case CMD_DISPLAY: {
            int number;
            scanf_s("%d", &number);
            remove_and_display(number);
            break;
        }

        case CMD_ERROR:
        default:
            break;
        }

    }
    return 0;
}
