
#include "tree.h"

#include <stdlib.h>

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

void tree_preorder(struct tree *t,
		void (*func)(double))
{
	if(!t) {
		return;
	}

	func(t->data);
	tree_preorder(t->left, func);
	tree_preorder(t->right, func);
}

void tree_inorder(struct tree *t,
		void (*func)(double))
{
	if(!t) {
		return;
	}

	tree_inorder(t->left, func);
	func(t->data);
	tree_inorder(t->right, func);
}


void tree_postorder(struct tree *t,
		void (*func)(double))
{
	if(!t) {
		return;
	}

	tree_postorder(t->left, func);
	tree_postorder(t->right, func);
	func(t->data);
}

