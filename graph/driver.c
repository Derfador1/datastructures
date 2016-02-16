
#include <stdbool.h>
#include <stdio.h>

#include "llist.h"
#include "hash.h"
#include "graph.h"

void print_item(const void *data, bool is_node)
{
	if(is_node) {
		printf("\n%s", (char *)data);
	} else {
		printf(u8" → %s", (char *)data);
	}
}

struct llist *graph_path(const graph *g, const void *from, const void *to)
{
	hash *visited = hash_create();
	
	hash_insert(visited, from, NULL); 

	hash_disassemble(visited);

	return NULL;
}

int main(void)
{
	graph *graphy = graph_create();

	graph_add_node(graphy, (void *)"A");
	graph_add_node(graphy, (void *)"B");
	graph_add_edge(graphy, (void *)"B", (void *)"A", 5);
	graph_add_node(graphy, (void *)"C");
	graph_add_node(graphy, (void *)"D");
	graph_add_edge(graphy, (void *)"B", (void *)"D", 5);
	graph_add_edge(graphy, (void *)"D", (void *)"B", 5);
	graph_add_edge(graphy, (void *)"C", (void *)"A", 5);
	graph_add_node(graphy, (void *)"E");

	graph_print(graphy, print_item);

	printf("\n%zu nodes, %zu edges\n", graph_node_count(graphy), graph_edge_count(graphy));

	struct llist *path = graph_path(graphy, (void *)"D", (void *)"A");
	struct llist *curr = path;
	while(curr) {
		printf(u8"%s → ", (char *)(curr->data));
		curr = curr->next;
	}
	printf("\n");
	ll_disassemble(path);

	graph_disassemble(graphy);
}
