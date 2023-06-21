#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string>
using std::string;

void ADD_BEG(int given_value);
void ADD_END(int given_value);
void DEL_BEG();
void DEL_END();
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
        if (function == "ADD_BEG")
        {
            std::cin >> parameter;
            ADD_BEG(parameter);
        }
        else if (function == "ADD_END")
        {
            std::cin >> parameter;
            ADD_END(parameter);
        }
        else if (function == "DEL_BEG")
            DEL_BEG();
        else if (function == "DEL_END")
            DEL_END();
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

void DEL_BEG()
{
    Node* temp = beginning;
    if (beginning != NULL)
    {
        //if (beginning == current)
        //{
        //    DEL_ACT();
        //    return;
        //}
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
        //if (end == current)
        //{
        //    DEL_ACT();
        //    return;
        //}
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