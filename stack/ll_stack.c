
#include <stdlib.h>

#include "stack.h"

stack *stack_create(void)
{
	stack *s = malloc(sizeof(*s));
	if(s) {
		s->head = NULL;
	}

	return s;
}

void stack_destroy(stack *s)
{
	if(!s) {
		return;
	}
	ll_destroy(s->head);
	free(s);
}

bool stack_is_empty(stack *s)
{
	if(!s || !s->head) {
		return true;
	}

	return false;
}

void stack_push(stack *s, double data)
{
	if(!s) {
		return;
	}

	struct llist *new_head = ll_create(data);
	if(!new_head) {
		return;
	}
	new_head->next = s->head;
	s->head = new_head;
}

double stack_pop(stack *s)
{
	if(stack_is_empty(s)) {
		return 0;
	}

	struct llist *old_head = s->head;
	double value = old_head->data;

	s->head = old_head->next;
	old_head->next = NULL;
	ll_destroy(old_head);

	return value;
}
