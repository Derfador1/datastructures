
#ifndef STACK_H
 #define STACK_H

#include <stdbool.h>

#ifdef STACK_ARRAY

#include <stdlib.h>
typedef struct {
	size_t head;
	size_t capacity;
	double *data;
} stack;

#else

#include "llist.h"
typedef struct {
	struct llist *head;
} stack;

#endif 

stack *stack_create(void);
void stack_destroy(stack *s);

bool stack_is_empty(stack *s);
void stack_push(stack *s, double data);
double stack_pop(stack *s);

#endif
