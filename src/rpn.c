
#include <stdio.h>
#include <string.h>

#include "stack.h"

int main(void)
{
	stack *numbers = stack_create();

	char input[64];
	char *pos = input;
	printf("Enter a calculation: ");
	fgets(input, sizeof(input), stdin);

	double term;
	char operator;
	while(*pos) {
		if(sscanf(pos, "%lf", &term)) {
			stack_push(numbers, term);
		} else if(sscanf(pos, "%c", &operator)) {
			switch(operator) {
				case '+':
					stack_push(numbers, stack_pop(numbers) + stack_pop(numbers));
					break;
				case '-':
					stack_push(numbers, stack_pop(numbers) - stack_pop(numbers));
					break;
				case '*':
					stack_push(numbers, stack_pop(numbers) * stack_pop(numbers));
					break;
				case '/':
					stack_push(numbers, stack_pop(numbers) / stack_pop(numbers));
					break;
			}
		}
		pos += strcspn(pos, " \t\n");
		pos += strspn(pos, " \t\n");
	}

	if(!stack_is_empty(numbers)) {
		fprintf(stderr, "Warning: Not all values used\n");
	}
	printf("%lf\n", stack_pop(numbers));

	stack_destroy(numbers);
}
