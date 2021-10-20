#include <stdio.h>
#include "tree.h"
#include "dialog.h"
#include "func.h"
const char *MSGS[] = {"0. Quit", "1. Add new element", "2. Delete element", "3. Find elements",
"4. Show the tree", "5. Find elements with the nearest key", "6. Show the tree in beautiful style",
"7. Add new elements with random", "8. Write tree in file", "9. Read tree from file",
"10. Delete tree", "11. Use graphviz", "12. Show the table in direct and reverse range"};
const int MSGS_SIZE = sizeof(MSGS) / sizeof(MSGS[0]);

int main()  {
    int a;
    Tree tree;
    tree.root = NULL;
    do {
        a = dialog(MSGS, MSGS_SIZE);
        switch(a) {
            case 0:
                puts("***Quit***");
                break;
            case 1:
                puts("***Add new element***");
                D_add(&tree);
                break;
            case 2:
                puts("***Delete element***");
                D_delete(&tree);
                break;
            case 3:
                puts("***Find elements***");
                D_find(&tree);
                break;
            case 4:
                puts("***Show the tree***");
                if (tree.root) {
                    show(tree.root);
                } else puts("Nothing to show. Tree is empty");
                break;
            case 5:
                puts("***Find elements with the nearest key***");
                D_find_near(&tree);
                break;
            case 6:
                puts("***Show the tree in beautiful style***");
                if (tree.root) {
                    puts("___________________________________");
                    format_show(tree.root, 0);
                    puts("___________________________________");
                } else puts("Nothing to show. Tree is empty");
                break;
            case 7:
                puts("***Add new elements with random***");
                D_add_random(&tree);
                break;
            case 8:
                puts("***Write tree in file***");
                D_write_file(&tree);
                break;
            case 9:
                puts("***Read tree from file***");
                D_read_file(&tree);
                break;
            case 10:
                puts("***Delete tree***");
                delete_tree(tree.root);
                tree.root = NULL;
                break;
            case 11:
                puts("***Use graphviz***");
                if (tree.root) {
                    puts("digraph G {");
                    graphviz_show(tree.root);
                    puts("}");
                } else puts("Nothing to show. Tree is empty");
                break;
            case 12:
                puts("***Show the table in direct and reverse range***");
                D_show_range(&tree);
                break;
        }
    } while (a != 0);
    delete_tree(tree.root);
    return 0;
}
