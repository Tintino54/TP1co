#include "fonctions.h"

int main(int argc, char *argv[])
{
	unsigned int i,j;
	char * filename = "DEFAYE_Johan.txt";
	int * edge_MST;

	unsigned int number_vertices = 0;
	unsigned int number_edges = 0;

	//get the number of vertices and the number of edges

	read_get_sizes(filename, &number_vertices, &number_edges);

	node nodes[number_vertices];
	edge edges[number_edges];

	//instanciate the arrays by reading the file
	read_create_arrays(filename, &nodes, &edges, number_vertices, number_edges);
	edge_MST = kruskal(edges, number_vertices, number_edges);
	
	for (i = 0; i < number_vertices-1; ++i) {
		printf("arête de %d", edges[edge_MST[i]].node_a);
		printf(" vers %d", edges[edge_MST[i]].node_b);
		printf(" de coût : %f \n \n", edges[edge_MST[i]].cost);
	}

	return 0;
}
