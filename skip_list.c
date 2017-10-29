#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include "inc/skip_list.h"

#define CONST_COIN 5 // Value reference to be used in insert function.

struct t_node
{
    int i;
    struct t_node *above, *below, *next, *prev;
};

struct t_skip_list
{
    struct t_skip_list *up_level, *down_level;
    NODE *head, *tail;
};

SKIP_LIST *skip_list_create()
{
    SKIP_LIST *new = NULL;
    new = (SKIP_LIST *) malloc(sizeof(SKIP_LIST));
    if(new != NULL)
    {
        new->up_level = NULL;
        new->down_level = NULL;
        new->head = (NODE *) malloc(sizeof(NODE));
        if(new ->head != NULL)
        {
            new->head->i = INT_MIN;
            new->head->above = NULL;
            new->head->below = NULL;
            new->head->prev = NULL;
            new->tail = (NODE *) malloc(sizeof(NODE));
            if(new->tail != NULL)
            {
                new->head->next = new->tail;
                new->tail->i = INT_MAX;
                new->tail->above = NULL;
                new->tail->below = NULL;
                new->tail->next = NULL;
                new->tail->prev = new->head;
            }
            else
            {
                free(new->head);
                printf("ERRO O CRIAR TAIL!\n");
            }
        }
        else
        {
            free(new);
            printf("ERRO AO CRIAR HEAD!\n");
        }
    }
    else
    {
        printf("ERRO AO CRIAR A SKIP LIST!\n");
    }

    return new;
}

void skip_list_insert(SKIP_LIST **list, int i)
{
    if((*list) != NULL)
    {
        SKIP_LIST *new_list = NULL;
        NODE *ptr = (*list)->head, *old = NULL;
        while(1) // Go to the deeper list, skipping the unecessary values
        {
            while(i > ptr->next->i) // Skip the unecessary values
            {
                ptr = ptr->next;
            }
            if(ptr->below != NULL)
            {
                ptr = ptr->below;
            }
            else
            {
                break;
            }
        }
        NODE *new = (NODE *) malloc(sizeof(NODE));
        if(new != NULL)
        {
            new->i = i;
            new->prev = ptr;
            new->next = ptr->next;
            new->below = NULL;
            new->above = NULL;
            ptr->next = new;
            srand(time(NULL));
            while((rand() % 10 + 1) > CONST_COIN) // Flip the coin, if get the value < 5, returns, otherwise insert node in the list at high level
            {
                old = new;
                while(ptr->prev != NULL && ptr->above == NULL) // Get the first node that have a node at high level list
                {
                    ptr = ptr->prev;
                }
                if(ptr->above != NULL) // if was found it
                {
                    ptr = ptr->above; // up one level
                    new = (NODE *) malloc(sizeof(NODE));
                    if(new != NULL)
                    {
                        old->above = new;
                        new->i = i;
                        new->prev = ptr;
                        new->next = ptr->next;
                        ptr->next = new;
                        new->below = old;
                        new->above = NULL;
                    }
                    else
                    {
                        printf("ERRO AO ALOCAR O NOVO NO ACIMA!\n");
                    }
                }
                else // There is no list above or there is no connection between the lists
                {
                    while(ptr->i != INT_MIN) // Then, we have to walk up to the first node in the list of the new inserted node
                    {
                        ptr = ptr->prev;
                    }
                    new_list = skip_list_create();
                    new_list->head->below = (*list)->head;
                    new_list->tail->below = (*list)->tail;
                    new_list->down_level = (*list);
                    (*list)->up_level = new_list;
                    if(new_list != NULL)
                    {
                        ptr = new_list->head;
                        new = (NODE *) malloc(sizeof(NODE));
                        if(new != NULL)
                        {
                            old->above = new;
                            new->i = i;
                            new->prev = ptr;
                            new->next = ptr->next;
                            ptr->next = new;
                            new->below = old;
                            new->above = NULL;
                            (*list) = new_list;
                        }
                        else
                        {
                            printf("ERRO AO ALOCAR O NOVO NO ACIMA!\n");
                        }
                    }
                    else
                    {
                        printf("ERRO AO CRIAR A NOVA LISTA ACIMA!\n");
                    }
                }
            }
        }
        else
        {
            printf("ERRO AO ALOCAR O NOVO NO!\n");
        }
    }
}

void skip_list_remove(SKIP_LIST *list, int n)
{
    if(list != NULL)
    {
        NODE *ptr = NULL, *aux = NULL;
        ptr = skip_list_search(list, n);
        if(ptr != NULL)
        {
            while(ptr->above != NULL)
            {
                ptr->prev->next = ptr->next;
                ptr->next->prev = ptr->prev;
                aux = ptr->above;
                free(ptr);
                ptr = aux;
            }
            ptr->prev->next = ptr->next;
            ptr->next->prev = ptr->prev;
            free(ptr);
        }
        else
        {
            printf("O ITEM A SER REMOVIDO NAO EXISTE!\n");
        }

    }
    else
    {
        printf("A SKIP LIST NAO EXISTE!\n");
    }
}

NODE *skip_list_search(SKIP_LIST *list, int n)
{
    NODE *ptr = NULL;
    if(list != NULL)
    {
        ptr = list->head;
        while(ptr->below != NULL)
        {
            if(ptr->next->i <= n)
            {
                ptr = ptr->next;
            }
            else
            {
                ptr = ptr->below;
            }
        }
        if(ptr->i != n)
        {
            while( ptr != NULL && ptr->i != n)
            {
                ptr = ptr->next;
            }
        }
    }
    else
    {
        printf("A SKIP LIST NAO EXISTE!\n");
    }
    return ptr;
}

void skip_list_print_node(NODE *nd)
{
    if(nd != NULL)
    {
        printf("%d\n", nd->i);
    }
}

void skip_list_delete(SKIP_LIST **list)
{
    if((*list) != NULL)
    {
        SKIP_LIST *ptr_list = NULL;
        NODE *ptr_node = NULL, *aux = NULL;
        while((*list) != NULL)
        {
            ptr_list = (*list);
            (*list) = (*list)->down_level;
            ptr_node = ptr_list->head;
            while(ptr_node != NULL)
            {
                aux = ptr_node;
                ptr_node = ptr_node->next;
                free(aux);
            }
            free(ptr_list);
        }
        (*list) = NULL;
    }
    else
    {
        printf("A SKIP LIST NAO EXISTE!\n");
    }
}
