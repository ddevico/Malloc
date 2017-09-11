#include "includes/malloc.h"

void tt(int *b)
{
    int *c;

    c = b;
    c +=6;
}

int main(void)
{
    int *b;
    int a;
    a=5;

    b = &a;
    printf("b = %d\n", *b);
    tt(b);
    printf("b = %d\n", *b);

    return 0;
}