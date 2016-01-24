#include "fonctions.h"

int main(int argc, char *argv[])
{
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
	
	//finding the index of each edge which belong to the Minimum Spaning Tree
	edge_MST = kruskal(edges, number_vertices, number_edges);
	
	//create the graphe with Latex
	create_latex_file(edges, nodes, number_vertices, number_edges);
	
	//create the MST with Latex
	create_latex_file_MST(edges, nodes, edge_MST, number_vertices, number_edges);
	return 0;
}
