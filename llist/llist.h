
#ifndef LLIST_H
 #define LLIST_H

#include <stdbool.h>

struct llist {
	double data;
	struct llist *next;
};

struct llist *ll_create(double data);
void ll_destroy(struct llist *l);

void ll_add(struct llist **l, double data);
void ll_remove(struct llist **l);


double ll_sum(struct llist *l);
void ll_print(struct llist *l);
void ll_append(struct llist *a,
		struct llist *b);
bool ll_is_circular(struct llist *l);
void ll_reverse(struct llist **l);

#endif
