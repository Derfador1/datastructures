
#include <stdio.h>

#include "llist.h"

int main(void)
{
	struct llist *list = ll_create(5.3);
	ll_add(&list, 3.1);
	ll_add(&list, 4.2);
	ll_add(&list, 6.0);
	ll_add(&list, -8.8);


	struct llist *tail = ll_create(9.5);
	ll_add(&tail, -1.7);
	ll_add(&tail, -19);

	ll_append(tail, tail);

	if(ll_is_circular(tail)) {
		printf("tail is circular\n");
	} else {
		printf("tail is NOT circular\n");
	}

	if(ll_is_circular(list)) {
		printf("list is circular\n");
	} else {
		printf("list is NOT circular\n");
	}



	ll_destroy(list);

}
