#include "listlist.h"

// Funcion que crea una lista de lista
ListList *ll_create()
{
    ListList *ll = (ListList *)malloc(sizeof(ListList));
    ll->len = 0;
    return ll;
}

// Funcion que muestra la lista de lista
void ll_print(ListList *listlist)
{
    for (unsigned long i = 0; i < listlist->len; i++)
    {
        list_print(&listlist->data[i]);
    }
    printf("\n");
}

// Funcion que libera la memoria de una lista de lista
void ll_free(ListList *listlist)
{
    if (listlist->len == 0)
    {
        free(listlist);
    }
    else
    {
        for (unsigned long i = 0; i < listlist->len; i++)
        {
            list_free(&listlist->data[i]);
        }
        free(listlist->data);
        free(listlist);
    }
}

// Funcion que agrega una nueva lista a la lista de listas
void ll_append(ListList *listlist, List new_element)
{
    if (listlist->len == 0)
    {
        listlist->data = (List *)malloc(sizeof(List));
        listlist->data[0] = new_element;
    }
    else
    {
        listlist->data = (List *)realloc(listlist->data, (listlist->len + 1) * sizeof(List));
        listlist->data[listlist->len] = new_element;
    }
    listlist->len++;
}

// Funcion que elimina una lista de la lista de lista
void ll_delete(ListList *listlist, unsigned long index)
{
    if (index < 0 || index > listlist->len)
    {
        printf("Posicion invalida! Por favor ingresar una posicion entre 1 y %lu", listlist->len);
    }
    else
    {
        list_free(&listlist->data[index]);
        for (unsigned long i = index; i < listlist->len - 1; i++)
        {
            listlist->data[i] = listlist->data[i + 1];
        }

        listlist->data = (List *)realloc(listlist->data, (listlist->len - 1) * sizeof(List));
        listlist->len--;
    }
}

// Funcion que elimina un elemento de la lista de lista
float ll_pop_min(ListList *listlist)
{
    float min = listlist->data[0].data[0];
    unsigned long index = 0;
    for (unsigned long i = 1; i < listlist->len; i++)
    {
        if (min > listlist->data[i].data[0])
        {
            min = listlist->data[i].data[0];
            index = i;
        }
    }
    min = list_pop(&listlist->data[index]);
    if (listlist->data[index].len == 0)
    {
        ll_delete(listlist, index);
    }
    return min;
}

// Funcino que verifica si la lista de lista esta vacia
int ll_is_empty(ListList *listlist)
{
    if (listlist->len == 0)
    {
        return 1;
    }
    for (unsigned long i = 0; i < listlist->len; i++)
    {
        if (listlist->data[i].len != 0)
        {
            return 0;
        }
    }
    return 1;
}

// Funcion que se encarga de ir verificando cada lista para seguir haciendo el merge entre ellas
void ll_merge(ListList *listlist, List *list)
{
    while (!ll_is_empty(listlist))
    {
        list_append(list, ll_pop_min(listlist));
    }
}

/*int main()
{
    ListList *ll = ll_create();
    List *l1 = list_create();
    list_append(l1, 1.2);
    list_append(l1, 1.3);
    list_append(l1, 1.8);
    list_append(l1, 2.4);
    list_append(l1, 3.3);
    List *l2 = list_create();
    list_append(l2,1.1);
    list_append(l2,1.4);
    list_append(l2,1.5);
    list_append(l2,2.1);
    list_append(l2,3.0);
    ll_append(ll,*l1);
    ll_append(ll,*l2);
    List *l3 = list_create();
    ll_merge(ll,l3);
    list_print(l3);
    ll_free(ll);
    return 0;
}*/