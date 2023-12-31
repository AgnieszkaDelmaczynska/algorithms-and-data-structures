#include <stdio.h>
using namespace std;
struct List_element
{
    char znak;
    List_element* next = 0;
};
struct List
{
    List_element* first = 0;
    void add_element(char sign);
    char delete_element(int  element_number);
};

int main()
{
    int how_many_equasions;
    scanf_s("%d", &how_many_equasions);
    List* lista = new List;
    for (int i = 0; i < how_many_equasions; i++)
    {
        char sign;
        int how_many_list_elements = 0;
        char temp_1, temp_2;
        if (i == 0) sign = getc(stdin);
        while (sign = getc(stdin))
        {
            if (sign == '\n') break;
            else if (sign == 't')
            {
                printf("    t\n");
                lista->add_element('t');
                how_many_list_elements++;
            }
            else if (sign == 'f')
            {
                printf("    f\n");
                lista->add_element('f');
                how_many_list_elements++;
            }
            else if (sign == 'N')
            {
                printf("    N\n");
                temp_1 = lista->delete_element(how_many_list_elements);
                if (temp_1 == 'f') temp_1 = 't';
                else temp_1 = 'f';
                lista->add_element(temp_1);
            }
            else if (sign == 'K')
            {
                printf("    K\n");
                temp_1 = lista->delete_element(how_many_list_elements);
                how_many_list_elements--;
                temp_2 = lista->delete_element(how_many_list_elements);
                if (temp_1 == 't' && temp_2 == 't') lista->add_element('t');
                else lista->add_element('f');
            }
            else if (sign == 'A')
            {
                printf("    A\n");
                temp_1 = lista->delete_element(how_many_list_elements);
                how_many_list_elements--;
                temp_2 = lista->delete_element(how_many_list_elements);
                if (temp_1 == 't' || temp_2 == 't') lista->add_element('t');
                else lista->add_element('f');
            }
        }
        temp_1 = lista->delete_element(1);
        printf("%c\n", temp_1);
    }
    delete lista;
    return 0;
}
void List::add_element(char sign)
{
    List_element* new_element = new List_element;
    new_element->znak = sign;
    if (first == 0)
    {
        first = new_element;
    }
    else
    {
        List_element* temporary = first;
        while (temporary->next != 0)
        {
            temporary = temporary->next;
        }
        temporary->next = new_element;
        new_element->next = 0;
    }
}
char List::delete_element(int element_number)
{

    if (element_number == 1)
    {
        List_element* temporary = first;
        char to_return = first->znak;
        first = temporary->next;
        delete temporary;
        return to_return;
    }
    else if (element_number > 1)
    {
        List_element* temporary = first;
        int actual_element = 1;
        while (true)
        {
            if (actual_element + 1 == element_number) break;
            temporary = temporary->next;
            actual_element++;
        }
        if (temporary->next->next == 0)
        {
            List_element* to_delete = temporary->next;
            char to_return = to_delete->znak;
            delete to_delete;
            temporary->next = 0;
            return to_return;
        }
        else
        {
            List_element* to_delete = temporary->next;
            char to_return = to_delete->znak;
            temporary->next = temporary->next->next;
            delete to_delete;
            return to_return;
        }
    }
    return 'a';
}