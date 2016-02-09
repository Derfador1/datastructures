
#define _BSD_SOURCE
#include "hash.h"

#include <string.h>

// static so that it will only be seen
// in this compilation unit
static const size_t DEFAULT_SIZE = 10;

static void h_llist_destroy(struct h_llist *list);
static struct h_llist *h_llist_create(const char *key, double value);
static size_t hashish(const char *key, size_t len);

hash *hash_create(void)
{
	hash *h = malloc(sizeof(*h));
	if(!h) {
		return NULL;
	}

	h->data = calloc(DEFAULT_SIZE,
			sizeof(*h->data));
	if(!h->data) {
		free(h);
		return NULL;
	}

	h->len = DEFAULT_SIZE;

	return h;
}

static void h_llist_destroy(struct h_llist *list)
{
	while(list) {
		struct h_llist *tmp = list->next;
		free(list->key);
		free(list);
		list = tmp;
	}
}

void hash_destroy(hash *h)
{
	if(h) {
		for(size_t n=0; n < h->len; ++n) {
			h_llist_destroy(h->data[n]);
		}

		free(h->data);
		free(h);
	}
}

static struct h_llist *h_llist_create(const char *key, double value)
{
	struct h_llist *node = malloc(sizeof(*node));
	if(!node) {
		return NULL;
	}

	node->key = strdup(key);
	if(!node->key) {
		free(node);
		return NULL;
	}
	node->value = value;
	node->next = NULL;

	return node;
}

static size_t hashish(const char *key,
		size_t len)
{
	return key[0] % len;
}

void hash_insert(hash *h,
		const char *key, double value)
{
	if(!h || !key) {
		return;
	}

	size_t idx = hashish(key, h->len);

	struct h_llist *new = h_llist_create(key, value);
	if(!new) {
		return;
	}

	// Add new value to head of linked list
	new->next = h->data[idx];
	h->data[idx] = new;
}

double hash_fetch(hash *h, const char *key)
{
	if(!h || !key) {
		return 0;
	}

	size_t idx = hashish(key, h->len);
	struct h_llist *tmp = h->data[idx];

	while(tmp) {
		if(strcmp(tmp->key, key) == 0) {
			return tmp->value;
		}

		tmp = tmp->next;
	}

	return 0;
}

