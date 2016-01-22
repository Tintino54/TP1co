#include "fonctions.h"
int main(int argc, char *argv[])
{
     FILE * fp;
       char * line = NULL;
       char ** exploded_string;
       int number_vertices;
       int number_edges;
       size_t len = 0;
       ssize_t read;

       fp = fopen("GINISTY_Valentin.txt", "r");
       if (fp == NULL)
           exit(EXIT_FAILURE);

        read = getline(&line, &len, fp);
        int line_counter = 1;
        exploded_string = str_split(line, ' ');
        number_vertices = atoi(exploded_string[0]);
        number_edges = atoi(exploded_string[1]);

        node nodes[number_vertices];
        edge edges[number_edges];

        int node_counter = 0;
        int edge_counter = 0;

       while ((read = getline(&line, &len, fp)) != -1) {
        //line = current line
           //printf("Retrieved line of length %zu :\n", read);
           //pour tous les noeuds
           if(line_counter <= number_vertices){
                printf("noeud : ");

                exploded_string = str_split(line, ' ');
                node new_node;
                new_node.x_node = atoi(exploded_string[0]);
                new_node.y_node = atoi(exploded_string[1]);
                new_node.id_node = node_counter+1;
                nodes[node_counter] = new_node;

                node_counter++;
           }
           //pour tous les arcs
           else{
                printf("arc : ");

                exploded_string = str_split(line, ' ');
                edge new_edge;
                new_edge.node_a = atoi(exploded_string[0]);
                new_edge.node_b = atoi(exploded_string[1]);
                new_edge.cost = atof(exploded_string[2]);
                edges[edge_counter] = new_edge;

                edge_counter++;
           }
            printf("%s", line);

            line_counter++;
       }

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

       fclose(fp);
       if (line)
           free(line);
       exit(EXIT_SUCCESS);

    return 0;
}
