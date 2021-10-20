#include "graph.h"
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
int add_node(Graph *graph, int x, int y, char *str) {
    for (int i = 0; i < graph->k; i++) {
        if (strcmp(graph->mas[i].str, str) == 0) {
            return -1;
        }
    }
    graph->k++;
    graph->mas = (Node *) realloc(graph->mas, graph->k * sizeof(Node));
    Node node;
    node.x = x;
    node.y = y;
    node.str = str;
    node.busy = 1;
    node.item = NULL;
    graph->mas[graph->k - 1] = node;
    return 0;
}

int delete_node(Graph *graph, char *str) {
    Node node;
    Item *item, *prev = NULL;
    int status = 1;
    int ind;
    for (int i = 0; i < graph->k; i++) {
        node = graph->mas[i];
        if (strcmp(node.str, str) == 0) {
            item = node.item;
            while (item) {
                prev = item;
                item = item->next;
                if (prev) free(prev);
            }
            free(node.str);
            graph->mas[i].str = NULL;
            graph->mas[i].busy = 0;
            ind = i;
            status = 0;
            break;
        }
    }

    if (status == 1) {
        return -1;
    } else {
        for (int i = 0; i < graph->k; i++) {
            node = graph->mas[i];
            if (node.busy == 0)
                continue;
            item = node.item;
            prev = NULL;
            while (item) {
                if (item->ind == ind) {
                    if (prev) {
                        prev->next = item->next;
                    }
                    if (item == node.item) {
                        node.item = item->next;
                    }
                    free(item);
                    break;
                }
                prev = item;
                item = item->next;
            }
        }
        return 0;
    }
}

int add_edge(Graph *graph, char *str1, char *str2, int w) { //ребро из str1 в str2
    int i;
    int ind1 = -1, ind2 = -1;
    for (i = 0; i < graph->k; i++) {
        if (strcmp(graph->mas[i].str, str1) == 0) {
            ind1 = i;
            break;
        }
    }
    if (ind1 < 0)
        return -1;
    for (i = 0; i < graph->k; i++) {
        if (strcmp(graph->mas[i].str, str2) == 0) {
            ind2 = i;
            break;
        }
    }
    if (ind2 < 0)
        return -2;
    Item *item = graph->mas[ind1].item;
    while (item) {
        if (strcmp(graph->mas[item->ind].str, str2) == 0)
            return -3;
        item = item->next;
    }
    item = NULL;
    item = (Item *) calloc(1, sizeof(Item));
    item->next = graph->mas[ind1].item;
    item->ind = ind2;
    item->w = w;
    graph->mas[ind1].item = item;
    return 0;
}

int delete_edge(Graph *graph, char *str1, char *str2) {
    int i;
    int ind;
    for (i = 0; i < graph->k; i++) {
        if (strcmp(graph->mas[i].str, str1) == 0) {
            ind = i;
            break;
        }
    }
    if (ind < 0)
        return -1;
    Item *item = graph->mas[ind].item, *prev = NULL;
    while (item) {
        if (strcmp(graph->mas[item->ind].str, str2) == 0) {
            if (prev) {
                prev->next = item->next;
            }
            if (item == graph->mas[ind].item) {
                graph->mas[ind].item = item->next;
            }
            free(item);
            return 0;
        }
        prev = item;
        item = item->next;
    }
    return -2;
}

void DFS_visit(Graph *graph, _DFS_ *dfs, int ind1, int ind2, int *time) {
    dfs[ind1].color = 1;
    *time = *time + 1;
    dfs[ind1].d = *time;
    Item *item = graph->mas[ind1].item;
    while (item) {
        if (dfs[item->ind].color == 0) {
            dfs[item->ind].pred = ind1;
            if (item->ind == ind2) {
                return;
            }
            DFS_visit(graph, dfs, item->ind, ind2, time);
        }
        item = item->next;
    }
    dfs[ind1].color = 2;
    *time = *time + 1;
    dfs[ind1].f = *time;
}

int DFS(Graph *graph, Way *way, char *str1, char *str2) {
    int i, ind1 = -1, ind2 = -1;
    _DFS_ *dfs = (_DFS_ *)calloc(graph->k, sizeof(_DFS_));
    for (i = 0; i < graph->k; i++) {
        if (graph->mas[i].busy == 0) {
            dfs[i].color = 2;
        } else dfs[i].color = 0;
        dfs[i].pred = -1;
        if (strcmp(graph->mas[i].str, str1) == 0) {
            ind1 = i;
        }
        if (strcmp(graph->mas[i].str, str2) == 0) {
            ind2 = i;
        }
    }
    if (ind1 < 0 || ind2 < 0) {
        free(dfs);
        return -2;
    }
    if (ind1 == ind2) {
        way->k = 1;
        way->mas = (int *)realloc(way->mas, way->k * sizeof(int));
        way->mas[0] = ind1;
        free(dfs);
        return 0;
    }
    int time = 0;
    DFS_visit(graph, dfs, ind1, ind2, &time);
    way->mas = (int *)realloc(way->mas, graph->k * sizeof(int));
    int ind = ind2;
    while (ind != -1) {
        way->mas[way->k] = ind;
        way->k++;
        if (ind == ind1) {
            way->mas = (int *)realloc(way->mas, way->k * sizeof(int));
            free(dfs);
            return 0;
        }
        ind = dfs[ind].pred;
    }
    free(dfs);
    return -1;
}

int BellFord(Graph *graph, Way *way, char *str1, char *str2) {
    int i, j, ind1 = -1, ind2 = -1;
    _BellFord_ *bf = (_BellFord_ *)calloc(graph->k, sizeof(_BellFord_));
    for (i = 0; i < graph->k; i++) {
        bf[i].pred = -1;
        bf[i].d = INT_MAX;
        if (graph->mas[i].busy == 0)
            continue;
        if (strcmp(graph->mas[i].str, str1) == 0) {
            ind1 = i;
            bf[i].d = 0;
        }
        if (strcmp(graph->mas[i].str, str2) == 0) {
            ind2 = i;
        }
    }
    if (ind1 < 0 || ind2 < 0) {
        free(bf);
        return -2;
    }
    Item *item;
    for (j = 1; j <= graph->k - 1; j++) {
        for (i = 0; i < graph->k; i++) {
            if (graph->mas[i].busy == 0)
                continue;
            item = graph->mas[i].item;
            while (item) {
                if (bf[i].d == INT_MAX) {
                    item = item->next;
                    continue;
                }
                if (bf[item->ind].d > bf[i].d + item->w) { //ослабление ребра
                    bf[item->ind].d = bf[i].d + item->w;
                    bf[item->ind].pred = i;
                }
                item = item->next;
            }
        }
    }

    way->mas = (int *)realloc(way->mas, graph->k * sizeof(int));
    int ind = ind2;
    int z = 0;
    while (ind != -1 && way->k < graph->k) {
        way->mas[way->k] = ind;
        way->k++;
        if (ind == ind1) {
            z = 1;
            way->mas = (int *)realloc(way->mas, way->k * sizeof(int));
            break;
        }
        ind = bf[ind].pred;
    }


    for (i = 0; i < way->k - 1; i++){
        ind1 = way->mas[i];
        ind2 = way->mas[i + 1];
        item = graph->mas[ind2].item;
        while (item) {
            if (item->ind == ind1) {
                if (bf[ind1].d > bf[ind2].d + item->w) {
                    free(bf);
                    return -3;
                }
                break;
            }
            item = item->next;
        }
    }
    free(bf);
    if (z == 0) {
        return -1;
    }
    return 0;

}

void find_3_min_index(Graph *graph, int **d, int a[3], int b[3]) {
    int i, j;
    int dist[3];
    for (i = 0; i < 3; i++) {
        dist[i] = INT_MAX;
    }
    for (i = 0; i < graph->k; i++) {
        if (graph->mas[i].busy == 0)
            continue;
        if (d[i][i] == 0) d[i][i] = INT_MAX;
        for (j = 0; j < graph->k; j++) {
            if (graph->mas[j].busy == 0)
                continue;
            if (d[i][j] <= dist[0] && d[i][j] != INT_MAX) {
                dist[2] = dist[1];
                a[2] = a[1];
                b[2] = b[1];
                dist[1] = dist[0];
                a[1] = a[0];
                b[1] = b[0];
                dist[0] = d[i][j];
                a[0] = i;
                b[0] = j;
            }
        }
    }
}

int Floyd_Warshall(Graph *graph, Way way[3]) {
    if (graph->k == 0)
        return -1;
    int i, j;
    Item *item;
    int **d, **pred;
    d = (int **)calloc(graph->k, sizeof(int *));
    pred = (int **)calloc(graph->k, sizeof(int *));

    for (i = 0; i < graph->k; i++) {
        d[i] = (int *)calloc(graph->k, sizeof(int));
        pred[i] = (int *)calloc(graph->k, sizeof(int));
        for (j = 0; j < graph->k; j++) {
            d[i][j] = INT_MAX;
            pred[i][j] = -1;
        }
        if (graph->mas[i].busy == 0)
            continue;
        d[i][i] = 0;
        item = graph->mas[i].item;
        while (item) {
            d[i][item->ind] = item->w;
            pred[i][item->ind] = i;
            item = item->next;
        }
    }

    int k;
    for (k = 0; k < graph->k; k++) {
        if (graph->mas[k].busy == 0)
            continue;
        for (i = 0; i < graph->k; i++) {
            if (graph->mas[i].busy == 0)
                continue;
            for (j = 0; j < graph->k; j++) {
                if (graph->mas[j].busy == 0)
                    continue;
                if (d[i][k] == INT_MAX || d[k][j] == INT_MAX) {
                    continue;
                }
                if (d[i][j] > d[i][k] + d[k][j]) {
                    d[i][j] = d[i][k] + d[k][j];
                    pred[i][j] = pred[k][j];
                }
            }
        }
    }
    int a[3] = {-1, -1, -1}, b[3] = {-1, -1, -1};
    find_3_min_index(graph, d, a, b);
    for (k = 0; k < 3; k++) {
        i = a[k];
        j = b[k];
        way[k].mas = (int *) calloc(graph->k, sizeof(int));
        while (j != -1 && i != -1 && way[k].k < graph->k) {
            printf("j = %d i = %d\n", j, i);
            way[k].mas[way[k].k] = j;
            way[k].k++;
            j = pred[i][j];
            if (j == i) {
                way[k].mas[way[k].k] = j;
                way[k].k++;
                way[k].mas = (int *) realloc(way[k].mas, way[k].k * sizeof(int));
                break;
            }
        }
    }

    for (i = 0; i < graph->k; i++) {
        free(pred[i]);
        free(d[i]);
    }
    free(pred);
    free(d);
    return 0;
}

void show_graph(Graph *graph) {
    for (int i = 0; i < graph->k; i++) {
        if (graph->mas[i].busy == 0)
            continue;
        printf("Name of node \"%s\" | Coordinates (%d, %d)| ", graph->mas[i].str, graph->mas[i].x, graph->mas[i].y);
        Item *item = graph->mas[i].item;
        while (item) {
            printf("|Name of dest node \"%s\"| Weight %d| ", graph->mas[item->ind].str, item->w);
            item = item->next;
        }
        printf("\n");
    }
}

void show_way(Graph *graph, Way *way) {
    puts("***WAY***");
    for (int i = way->k - 1; i >= 0; i--) {
        if (i == 0) {
            printf("%s", graph->mas[way->mas[i]].str);
        } else printf("%s -> ", graph->mas[way->mas[i]].str);
    }
    printf("\n");
}

void graphviz_show(Graph *graph) {
    Item *item;
    char *str;
    for (int i = 0; i < graph->k; i++) {
        if (graph->mas[i].busy == 0)
            continue;
        str = graph->mas[i].str;
        item = graph->mas[i].item;
        if (!item) printf("\"%s\"\n", str);
        while (item) {
            printf("\"%s\"->\"%s\"[label = %d]\n", str, graph->mas[item->ind].str, item->w);
            item = item->next;
        }
    }
}

void delete_graph(Graph *graph) {
    Node node;
    for (int i = 0; i < graph->k; i++) {
        if (graph->mas[i].busy == 0)
            continue;
        node = graph->mas[i];
        free(node.str);
        Item *item = node.item, *prev;
        while (item) {
            prev = item;
            item = item->next;
            free(prev);
        }
    }
    if (graph->k > 0)
        free(graph->mas);
    graph->mas = NULL;
    graph->k = 0;
}

int create_random(Graph *graph, int size) {
    if (size <= 0)
        return -1;
    delete_graph(graph);
    char *str = NULL;
    int x = 1, y = 2, t, i, j, w, k, n, status;
    srand(time(NULL));
    for (i = 0; i < size; i++) { //добавление вершин
        t = rand() % 10;
        str = (char *) calloc(t + 1, sizeof(char));
        for (j = 0; j < t; j++)
            str[j] = 'a' + rand() % 24; //61
        str[t] = '\0';
        status = add_node(graph, x, y, str);
        if (status == -1) free(str);
        str = NULL;
    }

    for (i = 0; i < graph->k; i++) { //добавление ребер
        k = rand() % (graph->k / 2);
        for (j = 0; j < k; j++) {
            w = rand() % 10000;
            if (rand() % 2 == 1)
                w = -w;
            n = rand() % k;
            add_edge(graph, graph->mas[i].str, graph->mas[n].str, w);
        }
    }
    return 0;
}

int file_write(char *name, Graph *graph) {
    FILE *file = fopen(name, "w+b");
    if (!file)
        return -1;
    if (graph->k == 0) {
        fclose(file);
        return -2;
    }
    int i, count, len;
    count = graph->k; //количество вершин
    int *pos = (int *) calloc(count, sizeof(int));
    Item *item;
    fseek(file, 0, SEEK_END);
    fwrite(&count, sizeof(int), 1, file);
    count = 0;
    for (i = 0; i < graph->k; i++) {
        if (graph->mas[i].busy == 0)
            continue;
        count++;
        pos[i] = ftell(file);
        fwrite(&(graph->mas[i].x), sizeof(int), 1, file);
        fwrite(&(graph->mas[i].y), sizeof(int), 1, file);
        len = strlen(graph->mas[i].str) + 1;
        fwrite(&len, sizeof(int), 1, file);
        fwrite(graph->mas[i].str, sizeof(char), len, file);
    }
    int item_pos, item_count;
    for (i = 0; i < graph->k; i++) {
        if (graph->mas[i].busy == 0)
            continue;
        item_pos = ftell(file);
        item_count = 0;
        fwrite(&item_count, sizeof(int), 1, file);
        item = graph->mas[i].item;
        while (item) {
            item_count++;
            fwrite(&pos[item->ind], sizeof(int), 1, file);
            fwrite(&(item->w), sizeof(int), 1, file);
            item = item->next;
        }
        fseek(file, item_pos, SEEK_SET);
        fwrite(&item_count, sizeof(int), 1, file);
        fseek(file, 0, SEEK_END);
    }

    fseek(file, 0, SEEK_SET);
    fwrite(&count, sizeof(int), 1, file);

    free(pos);
    fclose(file);
    return 0;
}

int file_read(char *name, Graph *graph) {
    FILE *file = fopen(name, "r+b");
    if (!file)
        return -1;
    delete_graph(graph);
    int i, j, count, len, x, y, w;
    char *str = NULL;
    fread(&count, sizeof(int), 1, file);
    for (i = 0; i < count; i++) {
        fread(&x, sizeof(int), 1, file);
        fread(&y, sizeof(int), 1, file);
        fread(&len, sizeof(int), 1, file);
        str = (char *) calloc(len, sizeof(char));
        fread(str, sizeof(char), len, file);
        add_node(graph, x, y, str);
        str = NULL;
    }
    Item *item;
    int item_count, pos, node_pos;
    for (i = 0; i < count; i++) {
        fread(&item_count, sizeof(int), 1, file);
        for (j = 0; j < item_count; j++) {
            fread(&node_pos, sizeof(int), 1, file);
            fread(&w, sizeof(int), 1, file);
            pos = ftell(file);
            fseek(file, node_pos + 2 * sizeof(int), SEEK_SET);
            fread(&len, sizeof(int), 1, file);
            str = (char *) calloc(len, sizeof(char));
            fread(str, sizeof(char), len, file);
            fseek(file, pos, SEEK_SET);
            add_edge(graph, graph->mas[i].str, str, w);
            free(str);
            str = NULL;
        }
    }
    fclose(file);
    return 0;
}
