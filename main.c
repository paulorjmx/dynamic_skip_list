#include <stdio.h>
#include <stdlib.h>
#include "inc/skip_list.h"

int main(int argc, char *argv[])
{
	SKIP_LIST *l = create();
	insert(&l, 1);
	insert(&l, 5);
	insert(&l, 2);
	insert(&l, 10);
	delete(&l);
	return 0;
}
