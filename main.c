#include "fonctions.h"
int main(int argc, char *argv[])
{
char * filename = "GINISTY_Valentin.txt";

int number_vertices = 0;
int number_edges = 0;

//get the number of vertices and the number of edges

read_get_sizes(filename, &number_vertices, &number_edges);

node nodes[number_vertices];
edge edges[number_edges];

//instanciate the arrays by reading the file
read_create_arrays(filename, &nodes, &edges, number_vertices, number_edges);


int i;
        for(i = 0; i < number_vertices; i++){
            printf("noeud numéro %d", nodes[i].id_node);
            printf(",x : %d", nodes[i].x_node);
            printf(" y : %d", nodes[i].y_node);
            printf("\n");
        }
int j;
        for(j = 0; j < number_edges; j++){
            printf("arrete de %d", edges[j].node_a);
            printf(" vers %d", edges[j].node_b);
            printf(" cout %f", edges[j].cost);
            printf("\n");
        }


    return 0;
}
