
#ifndef LLIST_H
 #define LLIST_H

#include <stdbool.h>

struct llist {
	const void *data;
	struct llist *next;
};

struct llist *ll_create(const void *data);
void ll_disassemble(struct llist *l);
void ll_destroy(struct llist *l);

void ll_add(struct llist **l, const void *data);
const void *ll_remove(struct llist **l);


void ll_append(struct llist *a,
		struct llist *b);
bool ll_is_circular(struct llist *l);
void ll_reverse(struct llist **l);

bool ll_is_sorted(struct llist *l,
		int (*cmp)(const void *, const void *));

#endif
