#include <stdio.h>
#include "defer.h"

int main(void)
{
    printf("Hello, World!\n");

    defer { printf("defer #1\n"); }
    defer { printf("defer #2\n"); }
    defer { printf("defer #3\n"); }

    printf("Goodbye, World!\n");

    return 0;
}