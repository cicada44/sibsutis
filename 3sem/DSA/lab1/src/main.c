#include <stdio.h>
#include "AVLTree.h"
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#define FEW 100000
#define LONG 1000000
#define clrcsl() printf("\e[1;1H\e[2J")

#define SIZE 50

void build()
{
    printf("      :::::::::      :::    :::       :::::::::::       :::        ::::::::: \n"
           "     :+:    :+:     :+:    :+:           :+:           :+:        :+:    :+: \n"
           "    +:+    +:+     +:+    +:+           +:+           +:+        +:+    +:+  \n"
           "   +#++:++#+      +#+    +:+           +#+           +#+        +#+    +:+   \n"
           "  +#+    +#+     +#+    +#+           +#+           +#+        +#+    +#+    \n"
           " #+#    #+#     #+#    #+#           #+#           #+#        #+#    #+#     \n"
           "#########       ########        ###########       ########## #########       \n");
}

void delete ()
{
    printf("      :::::::::       ::::::::::       :::             ::::::::::   :::::::::::       :::::::::: \n"
           "     :+:    :+:      :+:              :+:             :+:              :+:           :+:         \n"
           "    +:+    +:+      +:+              +:+             +:+              +:+           +:+          \n"
           "   +#+    +:+      +#++:++#         +#+             +#++:++#         +#+           +#++:++#      \n"
           "  +#+    +#+      +#+              +#+             +#+              +#+           +#+            \n"
           " #+#    #+#      #+#              #+#             #+#              #+#           #+#             \n"
           "#########       ##########       ##########      ##########       ###           ##########       \n");
}

int main()
{
    char *std_value = "1";

    struct avltree *tree = avltree_create(0, std_value);

    clrcsl();
    build();
    usleep(LONG);

    for (int x = 1; x < SIZE; x++)
    {
        clrcsl();
        tree = avltree_add(tree, x, std_value);
        avltree_print_dfs(tree, 1);
        usleep(FEW);
    }

    int h = avltree_height(tree);
    struct avltree *min = avltree_min(tree);
    struct avltree *max = avltree_max(tree);

    printf("\t\t\t\t\t\t\t\tHEIGHT - %d\n", h);
    printf("\t\t\t\t\t\t\t\tROOT - %d\n", tree->key);
    printf("\t\t\t\t\t\t\t\tMIN - %d\n", min->key);
    printf("\t\t\t\t\t\t\t\tMAX - %d\n", max->key);
    usleep(LONG);

    clrcsl();
    delete ();
    usleep(LONG);

    for (int x = SIZE; x >= 0; x--)
    {
        clrcsl();
        tree = avltree_delete(tree, x);
        avltree_print_dfs(tree, 1);
        usleep(FEW);
    }

    avltree_free(tree);

    return 0;
}