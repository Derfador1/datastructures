#include <stdio.h>

#include "bst.h"

void print_double(double value)
{
	printf("%lf\n", value);
}

int main(void)
{
	bst *mike_d = bst_create();

	bst_insert(mike_d, 57.2);
	bst_insert(mike_d, 87.2);
	bst_insert(mike_d, 80.2);
	bst_insert(mike_d, 50.0);
	bst_insert(mike_d, 10.0);
	bst_insert(mike_d, 90.1);

	tree_inorder(mike_d->root, print_double);

	bst_destroy(mike_d);
}
