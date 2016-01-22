
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

	char *buf = malloc(BUFLEN);
	if(!buf) {
		perror("Cannot initialize buffer");
		fclose(fp);
		return 7;
	}
	size_t hops = 0;

	struct llist *group = NULL;

	while(fgets(buf, BUFLEN, fp)) {
		if(ferror(fp)) {
			perror("Failed to read from file");
			ll_destroy(group);
			fclose(fp);
			free(buf);
			return 3;
		}
		if(!hops) {
			char *err = NULL;
			hops = strtol(buf, &err, 10);
			if(err && *err != '\n') {
				perror("First line must be a positive number");
				ll_destroy(group);
				fclose(fp);
				free(buf);
				return 4;
			}
			continue;
		}

		char *cpy = malloc(BUFLEN);
		if(!cpy) {
				ll_destroy(group);
				fclose(fp);
				free(buf);
		}

		char *nl = strchr(buf, '\n');
		if(!nl) {
			fprintf(stderr, "Name beginning '%s' is too long; max length of %zu allowed\n", buf, BUFLEN-1);
			return 9;
		}
		*nl = '\0';
		struct llist *cur = ll_create(strncpy(cpy, buf, BUFLEN));
		cur->next = group;
		group = cur;
	}
	fclose(fp);
	free(buf);

	ll_circlify(group);
	while(group != group->next) {
		size_t duck = hops;
		while(--duck) {
			group = group->next;
		}
		printf("%s is eliminated\n", (char *)group->next->data);
		remove_next(group);
		group = group->next;
	}

	printf("%s lives!\n", (char *)group->data);

	remove_next(group);
}
