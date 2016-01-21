
#include "llist.h"

#include <stdio.h>
#include <stdlib.h>


struct llist *ll_create(double data)
{
	struct llist *head = malloc(sizeof(*head));
	if(head) {
		head->data = data;
		head->next = NULL;
	}
	return head;
}

void ll_destroy(struct llist *l)
{
	while(l) {
		struct llist *tmp = l->next;
		free(l);
		l = tmp;
	}
}

void ll_add(struct llist **l, double data)
{
	struct llist *item = ll_create(data);
	if(item) {
		item->next = *l;
		*l = item;
	}
}

void ll_remove(struct llist **l)
{
	struct llist *old_head = *l;
	*l = old_head->next;
	old_head->next = NULL;
	ll_destroy(old_head);
}

double ll_sum(struct llist *l)
{
	double total = 0;
	while(l) {
		total += l->data;
		l = l->next;
	}
	return total;
}

void ll_print(struct llist *l)
{
	while(l) {
		printf("%lf -> ", l->data);
		l = l->next;
	}
	printf("NULL\n");
}

