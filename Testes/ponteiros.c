#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int main() {
    int t, j = 1, *p, *g;
    t = 5;
    p = &t;
    j = 3;
    g = &j;
    *p = (*g + t) * 2;
    *g = 4;
    g = p;
    for(j = 0; j < 2;j++) {
    *g = t*j + 1;
    }
    printf ("g%d\n", *g);
    printf ("j%d\n", j);
    *p = t + j + *g;
    printf ("p%d", *p);
}