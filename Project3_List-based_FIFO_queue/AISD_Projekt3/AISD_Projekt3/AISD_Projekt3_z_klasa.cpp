#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string>
using std::string;

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

class List {
private:
    Node* beginning, * end, * front, * front_prev, * back, * back_next;
public:
    List() {
        beginning = NULL;
        end = NULL;
        front = NULL;
        front_prev = NULL;
        back = NULL;
        back_next = NULL;
    }
    int size = 0;
    int count = 0;
    void ADD_BEG(int given_value);
    void ADD_END(int given_value);
    void DEL_BEG();
    void DEL_END();
    void PRINT_FORWARD() const;
    void PRINT_BACKWARD() const;
    void PUSH(int given_value);
    void POP();
    void PRINT_QUEUE();
    void GARBAGE_SOFT();
    void GARBAGE_HARD();
    bool check_if_is_in_queue(Node* node_to_check);
};

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);
    List lista;
    string function;
    int parameter;

    while (std::cin >> function)
    {
        if (function == "ADD_BEG")
        {
            std::cin >> parameter;
            lista.ADD_BEG(parameter);
        }
        else if (function == "ADD_END")
        {
            std::cin >> parameter;
            lista.ADD_END(parameter);
        }
        else if (function == "DEL_BEG")
            lista.DEL_BEG();
        else if (function == "DEL_END")
            lista.DEL_END();
        else if (function == "PRINT_FORWARD")
            lista.PRINT_FORWARD();
        else if (function == "PRINT_BACKWARD")
            lista.PRINT_BACKWARD();
        else if (function == "SIZE")
            printf("%d\n", lista.size);
        else if (function == "PUSH")
        {
            std::cin >> parameter;
            lista.PUSH(parameter);
        }
        else if (function == "POP")
            lista.POP();
        else if (function == "PRINT_QUEUE")
            lista.PRINT_QUEUE();
        else if (function == "COUNT")
            printf("%d\n", lista.count);
        else if (function == "GARBAGE_SOFT")
            lista.GARBAGE_SOFT();
        else if (function == "GARBAGE_HARD")
            lista.GARBAGE_HARD();
    }
    return 0;
}

void List::PUSH(int given_value)
{
    if (size == NULL)                                           // lista pusta
    {
        Node* new_node = (Node*)malloc(sizeof(Node));
        new_node->value = given_value;
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
            
            if (back == beginning)
            {
                new_node->npx = XOR(NULL, beginning);
                beginning->npx = XOR(new_node, XOR(beginning->npx, NULL));
                back = beginning = new_node;
                back_next = end;
                if (size == 1)
                    front_prev = back;
                else
                    if (front == end)
                        front_prev = beginning;
            }
            else
            {
                new_node->npx = XOR(front, back);
                front->npx = XOR(XOR(front->npx, back), new_node);
                back->npx = XOR(XOR(back->npx, front), new_node);
                back_next = front;
                back = new_node;
                front_prev = new_node;
            }
            size++;
            count++;
        }
    }
}

void List::POP()
{
    Node* temp_front = front;
    if (count == 0)
    {
        printf("NULL\n"); return;
    }
    if ((count == 1) && (size == 1))
        front_prev = front = back_next = back = NULL;
    //if ((count == 1) && (size == 2))
        
    if ((count == 2) && (size == 2)) {
        front_prev = front;
        front = back;}
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
        else if (front == beginning)
        {
            front_prev = front;
            front = end;
        }
        else
        {
            front = XOR(front->npx, front_prev);
            front_prev = temp_front;
        }
    }
    printf("%d\n", temp_front->value);
    count--;
}

void List::ADD_BEG(int given_value)
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
    if (check_if_is_in_queue(new_node) == true)
        count++;
}

void List::ADD_END(int given_value)
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
        if (check_if_is_in_queue(new_node) == true)
            count++;
    }
    else                                                    // jeśli lista jest pusta, to dodaj element jak ADD_BEG, będzie mniej nadmiarowego kodu
        List::ADD_BEG(given_value);
}

void List::DEL_BEG()
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
        if (check_if_is_in_queue(temp) == false)
            count--;
        size--;
        free(temp);
    }
}

void List::DEL_END()
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
        if ((back != front) && (back == temp))              //............OK
        {
            back = beginning;
            back_next = end;
        }
        if (check_if_is_in_queue(temp) == false)
            count--;
        size--;
        free(temp);
    }
}

bool List::check_if_is_in_queue(Node* node_to_check)
{
    bool is_in_queue = false;
    Node* temp_after_beg = beginning->npx;
    Node* temp_before_end = end->npx;
    beginning->npx = XOR(end, temp_after_beg);
    end->npx = XOR(temp_before_end, beginning);
                                                // ustawienie na listę cykliczną
    Node* tmp_current, * tmp_prev, * tmp_next;  // wskaźniki iterujące po liście
    tmp_current = front;                        // zaczynamy od początku listy
    tmp_prev = front_prev;
    while (tmp_current != back)
    {
        if (tmp_current == node_to_check)
            is_in_queue = true;
        tmp_next = XOR(tmp_prev, tmp_current->npx);
        tmp_prev = tmp_current;
        tmp_current = tmp_next;
    }
    if (tmp_current == back)
        if (tmp_current == node_to_check)
            is_in_queue = true;
    beginning->npx = temp_after_beg;
    end->npx = temp_before_end;
    return is_in_queue;
}

void List::GARBAGE_SOFT()
{
    //printf("garbage soft:\n");
    Node* tmp_current, * tmp_prev, * tmp_next;
    tmp_current = beginning;
    tmp_prev = NULL;
    if (tmp_current == NULL)
        return;
    while (tmp_current != NULL)
    {
        if (List::check_if_is_in_queue(tmp_current) == false)
            tmp_current->value = 0;
        tmp_next = XOR(tmp_prev, tmp_current->npx);
        tmp_prev = tmp_current;
        tmp_current = tmp_next;
    }
}
void List::GARBAGE_HARD()
{
    //printf("garbage hard:\n");
    List::GARBAGE_SOFT();
    Node* tmp_current, * tmp_prev, * tmp_next = XOR(beginning->npx, NULL);
    tmp_current = beginning;
    tmp_prev = NULL;
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
    back_next = front;
    front_prev = back;
}

void List::PRINT_QUEUE()
{
    //printf("queue forward:\n");
    if (count == 0)
    {
        printf("NULL\n"); return;
    }
    Node* temp_after_beg = beginning->npx;
    Node* temp_before_end = end->npx;
    beginning->npx = XOR(end, temp_after_beg);
    end->npx = XOR(temp_before_end, beginning);
    Node* tmp_current, * tmp_prev, * tmp_next;
    tmp_current = front;
    tmp_prev = front_prev;
    while (tmp_current != back)
    {
        printf("%d ", tmp_current->value);
        tmp_next = XOR(tmp_prev, tmp_current->npx);
        tmp_prev = tmp_current;
        tmp_current = tmp_next;
    }
    if (tmp_current == back)
        printf("%d ", tmp_current->value);
    printf("\n");
    beginning->npx = temp_after_beg;
    end->npx = temp_before_end;
}

void List::PRINT_FORWARD() const
{
    //printf("list forward:\n");
    Node* tmp_current, * tmp_prev, * tmp_next;
    tmp_current = beginning;
    tmp_prev = NULL;
    if (tmp_current == NULL)
    {
        printf("NULL\n"); return;
    }
    while (tmp_current != NULL)
    {
        printf("%d ", tmp_current->value);
        tmp_next = XOR(tmp_prev, tmp_current->npx);
        tmp_prev = tmp_current;
        tmp_current = tmp_next;
    }    printf("\n");
}

void List::PRINT_BACKWARD() const
{
    //printf("list backward:\n");
    Node* tmp_current, * tmp_prev, * tmp_next;
    tmp_current = end;
    tmp_next = NULL;
    if (tmp_current == NULL)
    {
        printf("NULL\n"); return;
    }
    while (tmp_current != NULL)
    {
        printf("%d ", tmp_current->value);
        tmp_prev = XOR(tmp_next, tmp_current->npx);
        tmp_next = tmp_current;
        tmp_current = tmp_prev;
    }   printf("\n");  
}