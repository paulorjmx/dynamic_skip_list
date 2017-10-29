#include <stdio.h>
#include <stdlib.h>
#include "inc/skip_list.h"

int main(int argc, char *argv[])
{
	SKIP_LIST *l = skip_list_create();
	skip_list_insert(&l, 1);
	skip_list_insert(&l, 2);
	skip_list_insert(&l, 5);
	skip_list_insert(&l, 10);
	skip_list_insert(&l, 22);
	skip_list_insert(&l, 21);
	skip_list_insert(&l, 32);
	skip_list_insert(&l, 4);
	skip_list_remove(l, 5);
	NODE *f = skip_list_search(l, 5);
	if(f != NULL)
	{
		skip_list_print_node(f);
	}
	else
	{
		printf("O ITEM NAO EXISTE\n");
	}
	skip_list_insert(&l, 110);
	skip_list_insert(&l, 222);
	skip_list_insert(&l, 211);
	skip_list_insert(&l, 34);
	skip_list_insert(&l, 44);
	f = skip_list_search(l, 110);
	if(f != NULL)
	{
		skip_list_print_node(f);
	}
	else
	{
		printf("O ITEM NAO EXISTE\n");
	}
	skip_list_delete(&l);
	return 0;
}
