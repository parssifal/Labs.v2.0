#include "func.h"
#include "dialog.h"
#include "graph.h"
const char *MSGS[] = {"0. Quit", "1. Add new node", "2. Add new edge", "3. Delete node",
"4. Delete edge", "5. Show graph", "6. Delete graph", "7. DFS find",
 "8. Find shortest way betweeen 2 nodes using Bellman Ford", "9. Find 3 shortest ways using Floyd Warshall",
 "10. Create graph with random", "11. Use graphviz", "12. Write graph in file", "13. Read graph from file"};
const int MSGS_SIZE = sizeof(MSGS) / sizeof(MSGS[0]);

int main()  {
    int a;
    Graph graph;
    graph.k = 0;
    graph.mas = NULL;

    do {
        a = dialog(MSGS, MSGS_SIZE);
        switch(a) {
            case 0:
                puts("***Quit***");
                break;
            case 1:
                puts("***Add new node***");
                D_add_node(&graph);
                break;
            case 2:
                puts("***Add new edge***");
                D_add_edge(&graph);
                break;
            case 3:
                puts("***Delete node***");
                D_delete_node(&graph);
                break;
            case 4:
                puts("***Delete edge***");
                D_delete_edge(&graph);
                break;
            case 5:
                puts("***Show graph***");
                if (graph.k > 0) {
                    show_graph(&graph);
                } else puts("Graph is empty");
                break;
            case 6:
                puts("***Delete graph***");
                delete_graph(&graph);
                break;
            case 7:
                puts("***DFS find***");
                D_DFS(&graph);
                break;
            case 8:
                puts("***Find shortest way betweeen 2 nodes using Bellman Ford***");
                D_BellFord(&graph);
                break;
            case 9:
                puts("***Find 3 shortest ways using Floyd Warshall***");
                D_Floyd_Warshall(&graph);
                break;
            case 10:
                puts("***Create graph with random***");
                D_create_random(&graph);
                break;
            case 11:
                puts("***Use graphviz***");
                if (graph.k > 0) {
                    puts("digraph G {");
                    graphviz_show(&graph);
                    puts("}");
                } else puts("Nothing to show. Graph is empty");
                break;
            case 12:
                puts("***Write graph in file***");
                D_write_file(&graph);
                break;
            case 13:
                puts("***Read graph from file***");
                D_read_file(&graph);
                break;
        }
    } while (a != 0);
    delete_graph(&graph);
    return 0;
}
