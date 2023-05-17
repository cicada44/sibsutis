#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void gen(int n)
{
    static int fn = 1;
    char bf[32];
    sprintf(bf, "data/%d.txt", fn);
    FILE* f = fopen(bf, "w");
    if (!f) {
        fprintf(stderr, "gen: fatal error: f == NULL\n");
        return;
    }
    while (n-- > 0) {
        fprintf(f, "%d\n", rand());
    }
    ++fn;
}

int main(int argc, char** argv)
{
    if (argc < 4)
        return 1;
    srand(time(0));
    int start = atoi(argv[1]);
    int end = atoi(argv[2]);
    int step = atoi(argv[3]);
    for (; start <= end; start += step) {
        gen(start);
    }
    return 0;
}
