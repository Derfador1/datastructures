
#include <stdio.h>

#include "tree.h"

void print_double(double value)
{
	printf("%lf\n", value);
}

int main(void)
{

	struct tree *stumpy = tree_create(18);

	stumpy->left = tree_create(97.2);
	stumpy->right = tree_create(-45.8);
	stumpy->right->left = tree_create(-5.9);
	stumpy->left->left = tree_create(0.2);

	tree_preorder(stumpy, print_double);
	puts("");
	tree_inorder(stumpy, print_double);
	puts("");
	tree_postorder(stumpy, print_double);

}
