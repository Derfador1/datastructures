
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../llist/llist.h"

const size_t BUFLEN = 64;

void ll_circlify(struct llist *l)
{
	struct llist *head = l;
	while(l->next) {
		l = l->next;
	}
	l->next = head;
}

void remove_next(struct llist *l)
{
	struct llist *to_remove = l->next;
	l->next = l->next->next;
	to_remove->next = NULL;
	ll_destroy(to_remove);
}

struct llist *read_file(FILE *fp, size_t *hops)
{
	if(!fp) {
		return NULL;
	}

	char *buf = malloc(BUFLEN);
	if(!buf) {
		perror("Cannot initialize buffer");
		return NULL;
	}

	// Extract the first line, which is the hopcount
	if(!fgets(buf, BUFLEN, fp)) {
		perror("Failed to read from file");
		goto failure;
	}
	char *err = NULL;
	*hops = strtol(buf, &err, 10);
	if(err && *err != '\n') {
		perror("First line must be a positive number");
		goto failure;
	}

	struct llist *head = NULL;
	struct llist *tail = head;

	while(fgets(buf, BUFLEN, fp)) {
		if(ferror(fp)) {
			perror("Failed to read from file");
			goto failure;
		}

		// These buffers are memory-managed by the list
		char *cpy = malloc(BUFLEN);
		if(!cpy) {
			perror("Ran out of space for names");
			goto failure;
		}

		char *nl = strchr(buf, '\n');
		if(!nl) {
			fprintf(stderr, "Name beginning '%s' is too long; max length of %zu allowed\n", buf, BUFLEN-1);
			goto failure;
		}
		*nl = '\0';

		struct llist *new_tail = ll_create(strncpy(cpy, buf, BUFLEN));
		if(!head) {
			head = new_tail;
			tail = head;
		} else {
			tail->next = new_tail;
			tail = new_tail;
		}
	}

	free(buf);
	ll_circlify(head);
	return head;

failure:
	ll_destroy(head);
	free(buf);
	return NULL;
}

int main(int argc, char *argv[])
{
	if(argc != 2) {
		fprintf(stderr, "Usage: %s <file>\n", argv[0]);
		return 1;
	}

	FILE *fp = fopen(argv[1], "r");
	if(!fp) {
		perror("Could not open file");
		return 2;
	}

	size_t hops = 0;

	struct llist *group = read_file(fp, &hops);
	fclose(fp);

	if(!group) {
		fprintf(stderr, "Exiting.\n");
		return 4;
	}

	while(group != group->next) {
		size_t duck = hops;
		struct llist *prev = group;
		// TODO: Does not work for a hop-count of 1
		while(--duck) {
			prev = group;
			group = group->next;
		}
		printf("%s is eliminated\n", (char *)group->data);
		remove_next(prev);
		group = prev->next;
	}

	printf("\n%s lives!\n", (char *)group->data);

	remove_next(group);
}
