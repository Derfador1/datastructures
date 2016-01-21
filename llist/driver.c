
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

	ll_print(list);
	ll_print(tail);
	printf("%lf\n", ll_sum(list));

	ll_append(list, tail);
	ll_print(list);

	printf("%lf\n", ll_sum(list));

	ll_print(tail);

	ll_destroy(list);

}
