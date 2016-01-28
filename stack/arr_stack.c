
#define STACK_ARRAY
#include "stack.h"

stack *stack_create(void)
{
	stack *s = malloc(sizeof(*s));
	if(!s) {
		return NULL;
	}

	s->head = 0;
	s->capacity = 2;
	s->data = malloc(s->capacity *
			sizeof(*s->data));
	if(!s->data) {
		free(s);
		return NULL;
	}

	return s;
}

void stack_destroy(stack *s)
{
	if(!s) {
		return;
	}
	free(s->data);
	free(s);
}

bool stack_is_empty(stack *s)
{
	if(!s || s->head == 0) {
		return true;
	}

	return false;
}

double stack_pop(stack *s)
{
	if(stack_is_empty(s)) {
		return 0;
	}
	
	return s->data[--(s->head)];
}

bool stack_push(stack *s, double data)
{
	if(!s) {
		return false;
	}

	if(s->head == s->capacity) {
		double * tmp = realloc(s->data,
				2 * s->capacity *
				sizeof(*s->data));
		if(!tmp) {
			return false;
		}
		s->data = tmp;
		s->capacity *= 2;
	}

	s->data[(s->head)++] = data;
	return true;
}

