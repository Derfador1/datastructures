
#include <stdio.h>

#include "llist.h"

int main(void)
{
	struct llist *list = ll_create(5.3);
	ll_add(&list, 3.1);
	ll_add(&list, 4.2);
	ll_add(&list, 6.0);
	ll_add(&list, -8.8);

	ll_print(list);

	printf("%lf\n", ll_sum(list));

	ll_destroy(list);

}
