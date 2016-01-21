
#include "double_llist.h"

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

void ll_append(struct llist *a,
		struct llist *b)
{
	while(a->next) {
		a = a->next;
	}

	a->next = b;
}

bool ll_is_circular(struct llist *l)
{
	struct llist *tmp = l;
	while(l && l->next != tmp) {
		l = l->next;
	}

	if(l == NULL) {
		return false;
	} else {
		return true;
	}
}

void ll_reverse(struct llist **l)
{
	struct llist *head = *l;
	struct llist *prev = NULL;
	while(head) {
		struct llist *after = head->next;
		head->next = prev;
		prev = head;
		head = after;
	}

	*l = prev;
}

bool ll_is_sorted(struct llist *l,
		int (*cmp)(double, double))
{
	while(l && l->next) {
		if(1 == cmp(l->data,
					l->next->data)) {
			return false;
		}
		l = l->next;
	}

	return true;
}

void ll_insert_increasing(
		struct llist **l,
		double data)
{
	struct llist *head = *l;
	struct llist *created = ll_create(data);
	struct llist *prev = NULL;

	while(head && head->data <= data) {
		prev = head;
		head = head->next;
	}

	created->next = head;
	if(prev) {
		prev->next = created;
	} else {
		// We are inserting at the head of this list
		*l = created;
	}

}
