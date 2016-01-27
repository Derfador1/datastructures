
#include <stdio.h>

#include "stack.h"

int main(void)
{
	stack *stacky = stack_create();

	stack_push(stacky, 82.1);
	stack_push(stacky, 51.3);
	stack_push(stacky, 89.99999);

	while(!stack_is_empty(stacky)) {
		printf("%lf\n", stack_pop(stacky));
	}

	stack_destroy(stacky);
}
