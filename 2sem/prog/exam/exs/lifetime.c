#include <stdio.h>

int global;
static int global_static;

int main(){
    int local = 4;
    static int local_static = 5;
    global_static = 5;
    printf("global - %d\n", global);
    printf("global - %d\n", global_static);
    // printf("global - %d\n", global_extern);
    printf("local - %d\n", local);
    printf("local_static - %d\n", local_static);

    return 0;
}