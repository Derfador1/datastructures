

#include <stdio.h>

#include "graph.h"

void print_item(const void *data, bool is_node)
{
	if(is_node) {
		printf("\n%c", (char)data);
	} else {
		printf(u8" → %c", (char)data);
	}
}

int main(void)
{
	graph *graphy = graph_create();

	graph_add_node(graphy, (void *)'A');
	graph_add_node(graphy, (void *)'B');
	graph_add_edge(graphy, (void *)'B', (void *)'A', 5);
	graph_add_node(graphy, (void *)'C');
	graph_add_node(graphy, (void *)'D');
	graph_add_edge(graphy, (void *)'B', (void *)'D', 5);
	graph_add_edge(graphy, (void *)'D', (void *)'B', 5);
	graph_add_edge(graphy, (void *)'C', (void *)'A', 5);
	graph_add_node(graphy, (void *)'E');

	graph_print(graphy, print_item);

	printf("\n%zu nodes, %zu edges\n", graph_node_count(graphy), graph_edge_count(graphy));

	graph_disassemble(graphy);
}
