
#include "tree.h"

struct tree *tree_create(double data)
{
	struct tree *t = malloc(sizeof(*t));
	if(t) {
		t->data = data;
		t->left = NULL;
		t->right = NULL;
	}

	return t;
}

void tree_destroy(struct tree *t)
{
	if(!t) {
		return;
	}

	tree_destroy(t->left);
	tree_destroy(t->right);
	free(t);
}


void tree_iterate(struct tree *t, void (*func)(double))
{
	if(!t) {
		return;
	}

	tree_iterate(t->left, func);
	tree_iterate(t->right, func);
	func(t->data);
}

