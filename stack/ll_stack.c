
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

void stack_push(stack *s, double data);
double stack_pop(stack *s);
