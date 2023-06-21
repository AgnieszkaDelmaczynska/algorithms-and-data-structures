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
void PUSH(int given_value);
void POP();
void PRINT_QUEUE();
void GARBAGE_SOFT();
void GARBAGE_HARD();

struct Node
{
    int value;
    struct Node* npx;
    bool queue = false;
};
// Function to return XOR
Node* XOR(Node* pointer_a, Node* pointer_c)                     //      XOR(a, c) = b            a   b   c
{
    return (Node*)((uintptr_t)pointer_a ^ (uintptr_t)pointer_c);
}

Node* beginning = NULL, * end = NULL, * front = NULL, * front_prev = NULL, * back = NULL, * back_next = NULL;
int size = 0;
int count = 0;

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
        else if (function == "SIZE")
            printf("%d\n", size);
        else if (function == "PUSH")
        {
            std::cin >> parameter;
            PUSH(parameter);
        }
        else if (function == "POP")
            POP();
        else if (function == "PRINT_QUEUE")
            PRINT_QUEUE();
        else if (function == "COUNT")
            printf("%d\n", count);
        else if (function == "GARBAGE_SOFT")
            GARBAGE_SOFT();
        else if (function == "GARBAGE_HARD")
            GARBAGE_HARD();
    }
    return 0;
}

void PUSH(int given_value)
{
    if (size == NULL)                                           // lista pusta
    {
        Node* new_node = (Node*)malloc(sizeof(Node));
        new_node->value = given_value;
        new_node->queue = true;
        new_node->npx = NULL;
        back_next = front_prev = back = front = end = beginning = new_node;
        size++;
        count++;
    }
    else                                                        // lista coś zawiera
    {
        if (count == 0)
        {
            end->value = given_value;
            end->queue = true;                                  // przypisz do kolejki
            back = front = end;
            if (size == 1)                                      //............OK
                back_next = front_prev = back = front;
            else                                                //............OK
            {
                back_next = XOR(end->npx, NULL);
                front_prev = beginning;
            }
            count++;
        }
        else if ((count >= 1) && (count < size))                //............OK
        {
            Node* temp_back = back;
            back_next->value = given_value;
            back_next->queue = true;                            // przypisz do kolejki
            back = back_next;
            if ((back_next != beginning) && (temp_back != beginning))
                back_next = XOR(back->npx, temp_back);
            else if (back_next == beginning)
                back_next = end;
            else if (temp_back == beginning)
                back_next = XOR(back->npx, NULL);
            count++;
        }
        else if (count == size)                                 //............OK
        {
            Node* new_node = (Node*)malloc(sizeof(Node));
            new_node->value = given_value;
            new_node->queue = true;
            new_node->npx = XOR(NULL, beginning);
            beginning->npx = XOR(new_node, XOR(beginning->npx, NULL));
            back = beginning = new_node;
            back_next = end;
            if (size == 1)
                front_prev = back;
            else
                if (front == end)
                    front_prev = beginning;
            size++;
            count++;
        }
    }
}
void POP()
{
    Node* temp_front = front;
    if (count == 0)
    {
        printf("NULL\n"); return;
    }       
    front->queue = false;
    if (count == 1)
        front_prev = front = back_next = back = NULL;
    if ((count == 2) && (size == 2))
        front = back_next = back;
    if ((count == 2) && (size != 2))
    {
        front = back;
        if (back == end)
            front_prev = beginning;
    }
    if (count >= 3)
    {
        if (front == end)// ok
        {
            front = XOR(front->npx, NULL);
            front_prev = end;
        }     
        else
        {
            front = XOR(front->npx, front_prev);
            front_prev = temp_front;
        }

    }
    printf("%d\n",temp_front->value);
    count--;
}
void ADD_BEG(int given_value)      // DZIAŁA
{
    Node* temp_beg = beginning;
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->value = given_value;

    if (beginning != NULL)                                  // jeśli nie jest pusta
    {
        new_node->npx = XOR(NULL, beginning);
        Node* temp_next = XOR(NULL, beginning->npx);
        beginning->npx = XOR(new_node, temp_next);
        beginning = new_node;
    }
    else                                                    // jeśli pusta lista
    {
        new_node->npx = NULL;                               // bo ((beginning == NULL) ^ (end == NULL)) == NULL
        end = beginning = new_node;
    }
    if (front == end)                                       //............OK
        front_prev = beginning;     
    if (back == temp_beg)                                   //............OK
        back_next = beginning;
    size++;
}

void ADD_END(int given_value)      // DZIAŁA
{
    Node* temp_end = end;
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->value = given_value;
    if (beginning != NULL)
    {
        new_node->npx = XOR(end, NULL);
        Node* temp_prev = XOR(end->npx, NULL);
        end->npx = XOR(temp_prev, new_node);
        end = new_node;
        if (front == temp_end)                              //............OK
            front_prev = end;       
        if (back == beginning)                              //............OK
            back_next = end;
        size++;
    }
    else                                                    // jeśli lista jest pusta, to dodaj element jak ADD_BEG, będzie mniej nadmiarowego kodu
    {
        ADD_BEG(given_value);
    }
}

void DEL_BEG()      // DZIAŁA
{
    Node* temp = beginning;
    if (beginning != NULL)
    {
        if (size == 1)                                      // 1 element
        {
            beginning = end = NULL;
            //return;
        }
        else if (size == 2)                                 // 2 elementy
        {                          
            end->npx = NULL;
            beginning = end;
        }
        else                                                // 3+ elementów
        {
            beginning = XOR(beginning->npx, NULL);          // jedno w prawo
            Node* temp_next = XOR(beginning->npx, temp);
            beginning->npx = XOR(NULL, temp_next);
        }
        if (back_next == temp)                              //............OK
            back_next = end;
        if (front_prev == temp)                             //............OK
            front_prev = XOR(front_prev->npx, NULL);
        if ((back != front) && (back == temp))              //............OK
            back = XOR(back->npx, NULL);
        else if ((back == front) && (back == temp))
            front = back = front_prev = back_next = NULL;          
        if ((back != front) && (front == temp))             //............OK
        {
            front = end;
            front_prev = XOR(temp->npx, NULL);
        }      
        size--;
        if (temp->queue == true)
            count--;
        free(temp);
    }
}

void DEL_END()      // DZIAŁA
{
    Node* temp = end;
    if (end != NULL)
    {
        if (size == 1)                                      // 1 element
        {
            beginning = end = NULL;
            //return;
        }
        else if (size == 2)                                 // 2 elementy
        {
            beginning->npx = NULL;
            end = beginning;
        }
        else                                                // 3+ elementów
        {
            end = XOR(end->npx, NULL);                      // jedno w lewo
            Node* temp_prev = XOR(end->npx, temp);
            end->npx = XOR(NULL, temp_prev);
        }
        if (front_prev == temp)                             //............OK
            front_prev = beginning;                             
        if (back_next == temp)                              //............OK
            back_next = XOR(back_next->npx, NULL);              
        if ((back != front) && (front == temp))             //............OK
            front = XOR(front->npx, NULL);                      
        else if ((back == front) && (front == temp))
            front = back = front_prev = back_next = NULL;
        if ((back != front) && (back == temp))               //............OK
        {
            back = beginning;
            back_next = end;
        }
        size--;
        if (temp->queue == true)
            count--;
        free(temp);
    }
}

void PRINT_QUEUE()
{
    //printf("queue forward:\n");
    Node* temp_after_beg = beginning->npx;
    Node * temp_before_end = end->npx;
    beginning->npx = XOR(end, temp_after_beg);
    end->npx = XOR(temp_before_end, beginning);
    if (count == 0)
    {
        printf("NULL\n");
        beginning->npx = temp_after_beg;
        end->npx = temp_before_end;
        return;
    }
    Node* tmp_current, * tmp_prev, * tmp_next;
    tmp_current = front;
    tmp_prev = front_prev;
    while (tmp_current != back)
    {
        if (tmp_current->queue == true)
            printf("%d ", tmp_current->value);
        tmp_next = XOR(tmp_prev, tmp_current->npx);
        tmp_prev = tmp_current;
        tmp_current = tmp_next;
    }
    if (tmp_current == back)
        if (tmp_current->queue == true)
            printf("%d ",tmp_current->value);
    printf("\n");
    beginning->npx = temp_after_beg;
    end->npx = temp_before_end;
}
void GARBAGE_SOFT()
{
    Node* tmp_current, * tmp_prev, * tmp_next;
    tmp_current = beginning;
    tmp_prev = NULL;
    //printf("garbage soft:\n");
    if (tmp_current == NULL)
        return;
    while (tmp_current != NULL)
    {
        if (tmp_current->queue != true)
            tmp_current->value = 0;
        tmp_next = XOR(tmp_prev, tmp_current->npx);
        tmp_prev = tmp_current;
        tmp_current = tmp_next;
    }
}
void GARBAGE_HARD()
{
    GARBAGE_SOFT();
    Node* tmp_current, * tmp_prev, * tmp_next = XOR(beginning->npx, NULL);
    tmp_current = beginning;
    tmp_prev = NULL;
    //printf("garbage hard:\n");
    if (tmp_current == NULL)
        return;
    while (tmp_current != NULL)
    {
        if (tmp_current->value == 0)
        {
            Node* tmp_tmp_current = tmp_current;
            if (size == 1)
            {
                tmp_current = beginning = end = NULL;
                size--;
                free(tmp_current);
                return;
            }
            else if (size > 1)
            {
                if (tmp_prev != NULL)
                    tmp_prev->npx = XOR(XOR(tmp_prev->npx, tmp_current), tmp_next);
                if (tmp_next != NULL)
                    tmp_next->npx = XOR(XOR(tmp_next->npx, tmp_current), tmp_prev);
                size--;               
            }
            tmp_next = XOR(tmp_prev, tmp_current->npx);
            tmp_current = tmp_next;
            tmp_next = XOR(tmp_prev, tmp_current->npx);
            free(tmp_tmp_current);
        }
        else
        {
            tmp_next = XOR(tmp_prev, tmp_current->npx);
            tmp_prev = tmp_current;
            tmp_current = tmp_next;
            if (tmp_current != NULL)
                tmp_next = XOR(tmp_prev, tmp_current->npx);
        }     
    }
}

void PRINT_FORWARD()
{
    Node* tmp_current, * tmp_prev, * tmp_next;
    tmp_current = beginning;
    tmp_prev = NULL;
    //printf("list forward:\n");
    if (tmp_current == NULL)
        {printf("NULL\n"); return;}
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
        {printf("NULL\n"); return;}
    while (tmp_current != NULL)
    {
        printf("%d ", tmp_current->value);
        tmp_prev = XOR(tmp_next, tmp_current->npx);
        tmp_next = tmp_current;
        tmp_current = tmp_prev;
    }
    printf("\n");
}