
#include <stdio.h>

#include "llist.h"

int increasing(double mint, double you)
{
	if(mint < you) {
		return -1;
	} else if(mint > you) {
		return 1;
	} else {
		return 0;
	}
}

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
	if(ll_is_sorted(tail, increasing)) {
		printf("tail is sorted\n");
	} else {
		printf("tail is NOT sorted\n");
	}
	if(ll_is_sorted(list, increasing)) {
		printf("list is sorted\n");
	} else {
		printf("list is NOT sorted\n");
	}

	ll_insert_increasing(&tail, 97);
	ll_insert_increasing(&tail, 0);
	ll_insert_increasing(&tail, -9001);
	ll_print(tail);

	ll_reverse(&list);
	ll_print(list);

	ll_destroy(list);

}
