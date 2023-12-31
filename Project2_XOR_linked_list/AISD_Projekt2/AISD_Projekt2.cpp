﻿#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string>
using std::string;

void ADD_BEG(int given_value);
void ADD_END(int given_value);
void ACTUAL();
void NEXT();
void PREV();
void DEL_ACT();
void DEL_BEG();
void DEL_END();
void ADD_ACT(int given_value);
bool DEL_VAL(int given_value);
void PRINT_FORWARD();
void PRINT_BACKWARD();

struct Node
{
    int value;
    struct Node* npx;
};
// Function to return XOR
Node* XOR(Node* pointer_a, Node* pointer_c)                     //      XOR(a, c) = b            a   b   c
{
    return (Node*)((uintptr_t)pointer_a ^ (uintptr_t)pointer_c);
}

Node* beginning = NULL, * end = NULL, * next = NULL, * current = NULL, * prev = NULL;

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);
    beginning = NULL;
    string function;
    int parameter;
    while (std::cin >> function)
    {
        if (function == "ACTUAL")
            ACTUAL();
        else if (function == "NEXT")
            NEXT();
        else if (function == "PREV")
            PREV();
        else if (function == "ADD_BEG")
        {
            std::cin >> parameter;
            ADD_BEG(parameter);
        }
        else if (function == "ADD_END")
        {
            std::cin >> parameter;
            ADD_END(parameter);
        }
        else if (function == "ADD_ACT")
        {
            std::cin >> parameter;
            ADD_ACT(parameter);
        }
        else if (function == "DEL_BEG")
            DEL_BEG();
        else if (function == "DEL_END")
            DEL_END();
        else if (function == "DEL_VAL")
        {
            std::cin >> parameter;
            while (DEL_VAL(parameter));
        }
        else if (function == "DEL_ACT")
            DEL_ACT();
        else if (function == "PRINT_FORWARD")
            PRINT_FORWARD();
        else if (function == "PRINT_BACKWARD")
            PRINT_BACKWARD();
    }
    return 0;
}

void ADD_BEG(int given_value)
{
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->value = given_value;

    if (beginning != NULL) // jeśli nie jest pusta
    {
        new_node->npx = XOR(NULL, beginning);
        Node* temp_next = XOR(NULL, beginning->npx);
        if (beginning == end)
        {
            next = new_node;
            prev = new_node;
        }
        else  // jeśli dwa elementy lub więcej
        {
            if (current == end)
            {
                next = new_node;
                prev = XOR(current->npx, NULL);
            }
            else if (current == beginning)
            {
                prev = new_node;
            }
        }
        beginning->npx = XOR(new_node, temp_next);
        beginning = new_node;
    }
    else  // jeśli pusta lista
    {
        new_node->npx = NULL;   // bo ((beginning == NULL) ^ (end == NULL)) == NULL
        prev = next = current = end = beginning = new_node;
    }
}

void ADD_END(int given_value)
{
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->value = given_value;
    if (beginning != NULL)
    {
        new_node->npx = XOR(end, NULL);
        Node* temp_prev = XOR(end->npx, NULL);
        if (beginning == end)
        {
            next = new_node;
            prev = new_node;
        }
        else  // jeśli dwa elementy lub więcej
        {
            if (current == end)
            {
                next = new_node;
            }
            else if (current == beginning)
            {
                prev = new_node;
                next = XOR(current->npx, NULL);
            }
        }
        end->npx = XOR(temp_prev, new_node);
        end = new_node;
    }
    else // jeśli lista jest pusta, to dodaj element jak ADD_BEG, będzie mniej nadmiarowego kodu
    {
        ADD_BEG(given_value);
    }
}

void ACTUAL()
{
    if (beginning == NULL) {printf("NULL\n");}
    else {printf("%d\n", current->value);//printf("ACTUAL %d\n", current->value);
    }
}

void NEXT()
{
    Node* temp1 = current;
    Node* temp2 = next;
    if (beginning == NULL)
    {
        printf("NULL\n");
        return;
    }
    else if (current == end)
    {
        next = beginning->npx;
        current = beginning;
        prev = end;
    }
    else
    {
        next = XOR(current, next->npx);
        current = temp2;
        prev = temp1;
    }
    printf("%d\n", current->value);
    //printf("NEXT %d\n", current->value);
}

void PREV()
{
    Node* temp1 = current;
    Node* temp2 = prev;
    if (beginning == NULL)
    {
        printf("NULL\n");
        return;
    }
    if (current == beginning)
    {
        prev = end->npx;
        current = end;
        next = beginning;
    }
    else
    {
        prev = XOR(prev->npx, current);
        current = temp2;
        next = temp1;
    }
    printf("%d\n", current->value);
    //printf("PREV %d\n", current->value);
}

void DEL_ACT()
{
    if (current != NULL)
    {
        Node* temp2 = prev;
        Node* temp = current;
        if (beginning == end) // DZIAŁA
        {
            current = next = prev = beginning = end = NULL;
            return;
        }
        else if ((beginning != end) && (next == prev))  // DZIAŁA
        {
            beginning = end;
            next->npx = prev->npx = beginning->npx = end->npx = current->npx = NULL;
            current = temp2;
        }
        else if (current == beginning)   // DZIAŁA
        {
            Node* temp_next_next = XOR(current, next->npx);
            prev = end->npx;
            current = end;
            next->npx = XOR(NULL, temp_next_next);
            beginning = next;
        }
        else if (current == end)    // DZIAŁA
        {
            prev = XOR(prev->npx, current);
            current = end->npx;
            current->npx = XOR(prev, NULL);
            end = current;
        }
        else    // DZIAŁA
        {
            Node* temp_next_next = XOR(current, next->npx);
            prev = XOR(prev->npx, current);
            current = temp2;
            current->npx = XOR(prev, next);
            next->npx = XOR(current, temp_next_next);
        }
        free(temp);
    }
}

void DEL_BEG()
{
    Node* temp = beginning;
    if (beginning != NULL)
    {
        if (beginning == current)
        {
            DEL_ACT();
            return;
        }
        if (beginning == end)// DZIAŁA              // jest 1 element (beg wskazuje na current)
        {
            current = next = prev = beginning = end = NULL;
            return;
        }
        else                                        // jest więcej niż 1 element
        {
            if (next == prev)                           // są 2 elementy
            {
                current = end;
                if (beginning == current)//DZIAŁA
                {
                    next->npx = NULL;
                    prev = current = beginning = next;
                }
                else//DZIAŁA
                {
                    current->npx = NULL;
                    next = prev = beginning = current;
                }
            }
            else                                        // jest 3+ elementów
            {
                Node* temp_next;
                temp_next = XOR(NULL, temp->npx);
                beginning = temp_next;
                if (beginning != NULL)
                {
                    Node* temp_next_next;
                    temp_next_next = XOR(temp, beginning->npx);
                    beginning->npx = XOR(NULL, temp_next_next);
                }
                if (temp == current)    // DZIAŁA
                {
                    current = prev;
                    prev = XOR(end->npx, NULL);
                }
                else if (temp == prev)  // DZIAŁA
                {
                    prev = beginning;
                }
                else if (temp == next)  // DZIAŁA
                {
                    next = beginning;
                }
            }
        }
        free(temp);
    }
}

void DEL_END()
{
    Node* temp = end;
    if (end != NULL)
    {
        if (end == current)
        {
            DEL_ACT();
            return;
        }
        if (beginning == end)// DZIAŁA              // jest 1 element (beg wskazuje na current)
        {
            current = next = prev = beginning = end = NULL;
            return;
        }
        else                                        // jest więcej niż 1 element
        {
            if (next == prev)                           // są 2 elementy
            {
                current = beginning;
                if (end == current)//DZIAŁA
                {
                    prev->npx = NULL;
                    next = current = beginning = prev;
                }
                else//DZIAŁA
                {
                    current->npx = NULL;
                    next = prev = beginning = current;
                }
            }
            else                                        // jest 3+ elementów
            {
                Node* temp_prev;
                temp_prev = XOR(temp->npx, NULL);
                end = temp_prev;
                if (end != NULL)                       //Gdy lista zawiera tylko jeden węzeł
                {
                    Node* temp_prev_prev;
                    temp_prev_prev = XOR(end->npx, temp);
                    end->npx = XOR(temp_prev_prev, NULL);
                }
                if (temp == current)    // DZIAŁA
                {
                    current = next;
                    next = XOR(beginning->npx, NULL);
                }
                else if (temp == next)  // DZIAŁA
                {
                    next = end;
                }
                else if (temp == prev)  // DZIAŁA
                {
                    prev = end;
                }               
            }
        }
        free(temp);
    }
}

void ADD_ACT(int given_value)                   // W KOŃCU DZIAŁA!!!!!!!!!!!!
{
    if (current != NULL)
    {
        Node* new_node = (Node*)malloc(sizeof(Node));
        new_node->value = given_value;

        if (current == beginning)  // DZIAŁA
        {
            Node* temp_prev_prev = XOR(prev->npx, NULL);
            new_node->npx = XOR(NULL, current);
            prev->npx = XOR(temp_prev_prev, NULL);
            prev = new_node;
            beginning = new_node;
            current->npx = XOR(prev, next);
        }
        else if (current == end)    // DZIAŁA
        {
            Node* temp_prev_prev = XOR(prev->npx, current);
            new_node->npx = XOR(prev, current);
            prev->npx = XOR(temp_prev_prev, new_node);
            prev = new_node;
            current->npx = XOR(prev, NULL);
        }
        else  // DZIAŁA
        {
            Node* temp_prev_prev = XOR(prev->npx, current);
            new_node->npx = XOR(prev, current);
            prev->npx = XOR(temp_prev_prev, new_node);
            prev = new_node;
            current->npx = XOR(prev, next);
        }
    }
}

bool DEL_VAL(int given_value)
{
    bool if_deleted = false;
    if (beginning == NULL)
    {
        return if_deleted;
    }
    Node* temp_prev_to_temp_current, * temp_next_to_temp_current, * temp_current, * temp2;
    temp_current = beginning;
    temp_prev_to_temp_current = NULL;
    temp2 = prev;
    //printf("delete value: %d\n", given_value);
    while (temp_current != NULL)
    {
        if (temp_current->value == given_value) // jeśli znaleziono element do usunięcia
        {
            if (beginning == end)       // 1 element             // DZIAŁA
            {
                free(end);
                current = next = prev = beginning = end = NULL;
                return if_deleted;
            }
            else // if (beginning != end)  1+ elementów
            {
                if_deleted = true;
                if (prev == next)       // 2 elementy
                {
                    Node* temp = current;
                    if ((temp_current == current) && (current == beginning))    // DZIAŁA
                    {
                        free(temp);
                        beginning = end;
                        next->npx = prev->npx = beginning->npx = end->npx = current->npx = NULL;
                        current = temp2;
                        return if_deleted;
                    }
                    else if ((temp_current == current) && (current == end))          // DZIAŁA
                    {
                        free(temp);
                        end = beginning;
                        next->npx = prev->npx = beginning->npx = end->npx = current->npx = NULL;
                        current = temp2;
                        return if_deleted;
                    }
                    else if ((temp_current != current) && (current == beginning))    // DZIAŁA
                    {
                        free(temp);
                        end = beginning;
                        next->npx = prev->npx = beginning->npx = end->npx = current->npx = NULL;
                        return if_deleted;
                    }
                    else if ((temp_current != current) && (current == end))          // DZIAŁA
                    {
                        free(temp);
                        beginning = end;
                        next->npx = prev->npx = beginning->npx = end->npx = current->npx = NULL;
                        return if_deleted;
                    }
                }
                else // if (prev != next)  3+ elementy
                {
                    if (temp_current == current)    // DZIAŁA
                    {
                        DEL_ACT();
                        return if_deleted;
                    }
                    else
                    {
                        if ((temp_current != beginning) && (temp_current != end))
                        {
                            temp_next_to_temp_current = XOR(temp_prev_to_temp_current, temp_current->npx);//OK
                            Node* temp_next_next = XOR(temp_next_to_temp_current->npx, temp_current);//OK
                            Node* temp_prev_prev = XOR(temp_prev_to_temp_current->npx, temp_current);//OK
                            temp_prev_to_temp_current->npx = XOR(temp_prev_prev, temp_next_to_temp_current);//OK
                            temp_next_to_temp_current->npx = XOR(temp_prev_to_temp_current, temp_next_next);//OK
                            return if_deleted;
                        }
                        if (temp_current == beginning)
                        {
                            DEL_BEG();
                            return if_deleted;
                        }
                        if (temp_current == end)
                        {
                            DEL_END();
                            return if_deleted;
                        }
                    }
                }
            }
        }
        else                                    // brak elementu do usunięcia, szukaj dalej w pętli
        {
            temp_next_to_temp_current = XOR(temp_prev_to_temp_current, temp_current->npx);
            temp_prev_to_temp_current = temp_current;
            temp_current = temp_next_to_temp_current;
        }
    }
    printf("\n");
    return if_deleted;
}

void PRINT_FORWARD()
{
    Node* tmp_current, * tmp_prev, * tmp_next;
    tmp_current = beginning;
    tmp_prev = NULL;
    //printf("list forward:\n");
    if (tmp_current == NULL)
    {
        printf("NULL\n");
        return;
    }
    while (tmp_current != NULL)
    {
        printf("%d ", tmp_current->value);
        tmp_next = XOR(tmp_prev, tmp_current->npx);
        tmp_prev = tmp_current;
        tmp_current = tmp_next;
    }
    printf("\n");
}

void PRINT_BACKWARD()
{
    Node* tmp_current, * tmp_prev, * tmp_next;
    tmp_current = end;
    tmp_next = NULL;
    //printf("list backward:\n");
    if (tmp_current == NULL)
    {
        printf("NULL\n");
        return;
    }
    while (tmp_current != NULL)
    {
        printf("%d ", tmp_current->value);
        tmp_prev = XOR(tmp_next, tmp_current->npx);
        tmp_next = tmp_current;
        tmp_current = tmp_prev;
    }
    printf("\n");
}