#include "fonctions.h"

char** str_split(char* a_str, const char a_delim)
{
    char** result    = 0;
    size_t count     = 0;
    char* tmp        = a_str;
    char* last_comma = 0;
    char delim[2];
    delim[0] = a_delim;
    delim[1] = 0;

    /* Count how many elements will be extracted. */
    while (*tmp)
    {
        if (a_delim == *tmp)
        {
            count++;
            last_comma = tmp;
        }
        tmp++;
    }

    /* Add space for trailing token. */
    count += last_comma < (a_str + strlen(a_str) - 1);

    /* Add space for terminating null string so caller
       knows where the list of returned strings ends. */
    count++;

    result = malloc(sizeof(char*) * count);

    if (result)
    {
        size_t idx  = 0;
        char* token = strtok(a_str, delim);

        while (token)
        {
            *(result + idx++) = strdup(token);
            token = strtok(0, delim);
        }
        *(result + idx) = 0;
    }

    return result;
}

void read_get_sizes(char * filename, int * number_vertices, int * number_edges){
    FILE * fp;
       char * line = NULL;
       char ** exploded_string;
       size_t len = 0;
       ssize_t read;

       fp = fopen(filename, "r");
       if (fp == NULL)
           exit(EXIT_FAILURE);

        read = getline(&line, &len, fp);
        int line_counter = 1;
        exploded_string = str_split(line, ' ');
        *number_vertices = atoi(exploded_string[0]);
        *number_edges = atoi(exploded_string[1]);
        fclose(fp);
       if (line)
           free(line);
}

void read_create_arrays(char * filename, node * nodes, edge * edges, int number_vertices, int number_edges){
        FILE * fp;
       char * line = NULL;
       char ** exploded_string;
       size_t len = 0;
       ssize_t read;

       fp = fopen("GINISTY_Valentin.txt", "r");
       if (fp == NULL)
           exit(EXIT_FAILURE);

        read = getline(&line, &len, fp);
        int line_counter = 1;
        int node_counter = 0;
        int edge_counter = 0;

       while ((read = getline(&line, &len, fp)) != -1) {
        //line = current line
           //printf("Retrieved line of length %zu :\n", read);
           //pour tous les noeuds
           if(line_counter <= number_vertices){
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
                exploded_string = str_split(line, ' ');
                edge new_edge;
                new_edge.node_a = atoi(exploded_string[0]);
                new_edge.node_b = atoi(exploded_string[1]);
                new_edge.cost = atof(exploded_string[2]);
                edges[edge_counter] = new_edge;

                edge_counter++;
           }

            line_counter++;
            }
            fclose(fp);
       if (line)
           free(line);

}
