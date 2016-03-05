
#include "llist.h"

#include <stdio.h>
#include <stdlib.h>


struct llist *ll_create(const void *data)
{
	struct llist *head = malloc(sizeof(*head));
	if(head) {
		head->data = data;
		head->next = NULL;
	}
	return head;
}

void ll_disassemble(struct llist *l)
{
	while(l) {
		struct llist *tmp = l->next;
		free(l);
		l = tmp;
	}
}

void ll_destroy(struct llist *l)
{
	while(l) {
		struct llist *tmp = l->next;
		free((void*)l->data);
		free(l);
		l = tmp;
	}
}

void ll_add(struct llist **l, const void *data)
{
	struct llist *item = ll_create(data);
	if(item) {
		item->next = *l;
		*l = item;
	}
}

const void *ll_remove(struct llist **l)
{
	struct llist *old_head = *l;
	*l = old_head->next;
	const void *data = old_head->data;
	free(old_head);
	return data;
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
		int (*cmp)(const void *, const void *))
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

void ll_print(struct llist *test)
{
	struct llist *tmp = test;

	while(tmp) {
		const struct device *data = tmp->data;
		printf(u8"%d → ", data->source_dev_id);
		//printf(u8"%d → ", data->count);
		//printf("Battery Power %.02lf%%\n", data->battery_power);
		tmp = tmp->next;
	}
}

void ll_removed_dev(struct llist *test)
{
	struct llist *tmp = test;

	while(tmp) {
		struct device *data = (struct device *)tmp->data;
		printf("Removing Device #%d\n", data->source_dev_id);
		tmp = tmp->next;
	}
}



void ll_test(struct llist *test)
{
	struct llist *tmp = test;

	while(tmp) {
		const struct device *data = tmp->data;
		printf(u8"%d → ", data->source_dev_id);
		printf(u8"%d → \n", data->count);
		//printf("Battery Power %.02lf%%\n", data->battery_power);
		tmp = tmp->next;
	}
}

unsigned int find_min(struct llist *l)
{
	int max = 0;

	struct llist *test = l;

	unsigned int source_id = 0;
	
	while(l) {
		struct device *tmp1 = (struct device *)l->data;

		if(tmp1->count > max) {
			max = tmp1->count;
		}
		else if(tmp1->count <= max) {
			source_id = tmp1->source_dev_id;
		}

		l = l->next;
	}

	l = test;
	return source_id;
}

//uses double pointers to remove nodes from a linked list but not lose data
void remover(struct llist **l, const void *data)
{
	struct llist **head;
	head = l;
	while(*head) {
		if((*head)->data == data) {
			void *to_free = *head;
			*head = (*head)->next;
			free(to_free);
		}

		if(!*head) {
			return;
		}

		head = &((*head)->next); //sets head to the address or the thing at heads next
	}
}

//small function to walk through and reset the count to 0
void count_reseter(struct llist *l)
{
	while(l) {
		struct device *tmp1 = (struct device *)l->data;
		tmp1->count = 0;
		l = l->next;
	}
}
