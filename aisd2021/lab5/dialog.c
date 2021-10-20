#include "func.h"
#include "graph.h"
#include <stdlib.h>
#include <time.h>

int D_add_node(Graph *graph) {
    int status, x, y;
    puts("Enter coordinates");
    status = get_int(&x);
    if (status == -1) {
        return -1;
    }
    status = get_int(&y);
    if (status == -1) {
        return -1;
    }
    char *str = NULL;
    puts("Enter name of node");
    str = get_str();
    if (!str) {
        return -1;
    }
    status = add_node(graph, x, y, str);
    if (status == -1) {
        puts("Node with this name already exists");
        free(str);
        return -1;
    } else {
        puts("Element was added");
        return 0;
    }
}

int D_add_edge(Graph *graph) {
    char *str1 = NULL, *str2 = NULL;
    puts("Enter name of source node");
    str1 = get_str();
    if (!str1) {
        return -1;
    }
    puts("Enter name of destination node");
    str2 = get_str();
    if (!str2) {
        free(str1);
        return -1;
    }
    int status, w;
    puts("Enter weight of edge");
    status = get_int(&w);
    if (status == -1) {
        free(str1);
        free(str2);
        return -1;
    }
    status = add_edge(graph, str1, str2, w);
    if (status == -1) {
        printf("Node with name \"%s\" doesn't exist", str1);
    }
    if (status == -2) {
        printf("Node with name \"%s\" doesn't exist", str2);
    }
    if (status == -3) {
        printf("Edge between these nodes already exist\n");
    }
    if (status == 0) {
        puts("Edge was added");
    }
    free(str1);
    free(str2);
    return 0;
}

int D_delete_node(Graph *graph) {
    char *str;
    puts("Enter name of deleting node");
    str = get_str();
    if (!str)
        return -1;
    int status;
    status = delete_node(graph, str);
    free(str);
    if (status == -1) {
        puts("Node with this name doesn't exist");
    } else puts("Node was deleted");
    return 0;
}

int D_delete_edge(Graph *graph) {
    char *str1 = NULL, *str2 = NULL;
    puts("Enter name of source node");
    str1 = get_str();
    if (!str1) {
        return -1;
    }
    puts("Enter name of destination node");
    str2 = get_str();
    if (!str2) {
        free(str1);
        return -1;
    }
    int status = delete_edge(graph, str1, str2);
    if (status == -1) {
        printf("Node with name \"%s\" doesn't exist", str1);
    }
    if (status == -2) {
        printf("Edge with dest name \"%s\" doesn't exist", str2);
    }
    if (status == 0) {
        puts("Edge was deleted");
    }
    free(str1);
    free(str2);
    return 0;
}

int D_create_random(Graph *graph) {
    int status, size;
    puts("Enter size of graph you want to create");
    status = get_int(&size);
    if (status == -1)
        return -1;
    status = create_random(graph, size);
    if (status == -1) {
        puts("Size <= 0. Graph is empty");
        return -1;
    }
    puts("Graph was successfully created");
    return 0;
}

int D_DFS(Graph *graph) {
    char *str1 = NULL, *str2 = NULL;
    puts("Enter name of source node");
    str1 = get_str();
    if (!str1) {
        return -1;
    }
    puts("Enter name of destination node");
    str2 = get_str();
    if (!str2) {
        free(str1);
        return -1;
    }
    Way way;
    way.k = 0;
    way.mas = NULL;
    double time;
    clock_t start, end;
    start = clock();
    int status = DFS(graph, &way, str1, str2);
    end = clock();
    time = (double)(end - start) / CLOCKS_PER_SEC;
    free(str1);
    free(str2);
    if (status == -2) {
        puts("There is no element with this name");
        return -2;
    }
    if (status == -1) {
        printf("Time: %.15lf\n", time);
        puts("Way between these node doesn't exist");
        free(way.mas);
        return -1;
    }
    printf("Time: %.15lf\n", time);
    show_way(graph, &way);
    free(way.mas);
    return 0;
}

int D_BellFord(Graph *graph) {
    char *str1 = NULL, *str2 = NULL;
    puts("Enter name of source node");
    str1 = get_str();
    if (!str1) {
        return -1;
    }
    puts("Enter name of destination node");
    str2 = get_str();
    if (!str2) {
        free(str1);
        return -1;
    }
    Way way;
    way.k = 0;
    way.mas = NULL;
    double time;
    clock_t start, end;
    start = clock();
    int status = BellFord(graph, &way, str1, str2);
    end = clock();
    time = (double)(end - start) / CLOCKS_PER_SEC;
    free(str1);
    free(str2);
    if (status == -2) {
        puts("There is no element with this name");
        return -2;
    }
    if (status == -1) {
        printf("Time: %.15lf\n", time);
        puts("Way between these node doesn't exist");
        free(way.mas);
        return -1;
    }
    if (status == -3) {
        printf("Time: %.15lf\n", time);
        puts("Way between these node has negative cycles");
        free(way.mas);
        return -1;
    }
    printf("Time: %.15lf\n", time);
    show_way(graph, &way);
    free(way.mas);
    return 0;
}

int D_Floyd_Warshall(Graph *graph) {
    Way way[3];
    int i;
    for (i = 0; i < 3; i++) {
        way[i].k = 0;
        way[i].mas = NULL;
    }
    double time;
    clock_t start, end;
    start = clock();
    int status = Floyd_Warshall(graph, way);
    end = clock();
    time = (double)(end - start) / CLOCKS_PER_SEC;
    if (status == -1) {
        puts("Graph is empty");
        return -1;
    }

    for (i = 0; i < 3; i++) {
        if (way[i].k > 0) {
            show_way(graph, &(way[i]));
        } else printf("Way number %d doesn't exist\n", i + 1);
        free(way[i].mas);
    }
    printf("Time: %.15lf\n", time);
    return 0;
}

int D_write_file(Graph *graph) {
    if (graph->k == 0) {
        puts("Graph is empty");
        return -1;
    }
    puts("Enter name of file");
    char *name = get_str();
    if (!name)
        return -1;
    int status = file_write(name, graph);
    free(name);
    if (status == -1) {
        puts("File couldn't be opened");
        return -1;
    }
    puts("Information was successfully written");
    return 0;
}

int D_read_file(Graph *graph) {
    puts("Enter name of file");
    char *name = get_str();
    if (!name)
        return -1;
    int status = file_read(name, graph);
    free(name);
    if (status == -1) {
        puts("File with this name wasn't found");
        return -1;
    }
    puts("Information was successfully read");
    return 0;
}

