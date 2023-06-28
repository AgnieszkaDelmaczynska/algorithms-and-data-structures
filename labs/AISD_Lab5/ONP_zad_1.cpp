#include <iostream>
#include <stdio.h>
using namespace std;

struct Element_of_list
{
    Element_of_list* next = 0;
    char sign_of_element;
};
struct List
{
    Element_of_list* first=0;
    char delete_an_element(int  element_number);
    void add_an_element(char sign);
};

int main()
{
    int how_many_inputs;
    cin >> how_many_inputs;
    List *list = new List;
    for (int i = 0; i < how_many_inputs; i++)
    {
        int how_many_list_elements = 0;
        char temp1, temp2;
        char sign;
        if (i == 0) 
            sign = getc(stdin);
        while (sign = getc(stdin))
        {
            if (sign == 't')
            {
                list->add_an_element('t');
                how_many_list_elements++;
            }
            else if (sign == 'f')
            {
                list->add_an_element('f');
                how_many_list_elements++;
            }
            else if (sign == 'N')
            {
                temp1 = list->delete_an_element(how_many_list_elements);
                if (temp1 == 't')
                    temp1 = 'f';
                else
                    temp1 = 't';
                list->add_an_element(temp1);
            }
            else if (sign == 'A')
            {
                temp1 = list->delete_an_element(how_many_list_elements);
                how_many_list_elements--;
                temp2 = list->delete_an_element(how_many_list_elements);
                if (temp1 == 't' || temp2 == 't')
                    list->add_an_element('t');
                else
                    list->add_an_element('f');
            }
            else if (sign == 'K')
            {
                temp1 = list->delete_an_element(how_many_list_elements);
                how_many_list_elements--;
                temp2 = list->delete_an_element(how_many_list_elements);
                if (temp1 == 't' && temp2 == 't')
                    list->add_an_element('t');
                else
                    list->add_an_element('f');
            }
            else if (sign == '\n')
                break;
        }
        temp1 = list->delete_an_element(1);
        printf("%c\n", temp1);
    }
    delete list;
    return 0;
}

void List::add_an_element(char sign)
{
    Element_of_list* new_element = new Element_of_list;
    new_element->sign_of_element = sign;
    if (first != 0)
    {
        Element_of_list* temporary = first;
        while (temporary->next != 0)
        {
            temporary = temporary->next;
        }
        temporary->next = new_element;  
        new_element->next = 0;
    }
    else
        first = new_element;
}

char List::delete_an_element(int element_number)
{    
    if (element_number > 1)
    {
        Element_of_list* temporary = first;
        int actual_element = 1; 
        while (true)
        {
            if (actual_element + 1 == element_number)
                break;
            temporary = temporary->next;
            actual_element++;
        }
        if (temporary->next->next == 0)
        {
            Element_of_list* to_delete = temporary->next;
            char to_return = to_delete->sign_of_element;
            delete to_delete;
            temporary->next = 0;
            return to_return;
        }
        else
        {
            Element_of_list* to_delete = temporary->next;
            char to_return = to_delete->sign_of_element;
            temporary->next = temporary->next->next;
            delete to_delete;
            return to_return;
        }
    }
    else if (element_number == 1)
    {
        Element_of_list* temporary = first;
        char to_return = first->sign_of_element;
        first = temporary->next;
        delete temporary;
        return to_return;
    }
    return 'x';
}