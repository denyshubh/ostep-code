#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include "common.h"


int
main (int args, char *argv[])
{
    int *p = malloc(sizeof(int)); // occupied 4 bytes of heap memory
    assert(p != NULL);  // check if malloc failed

    printf("(%d) address pointed to by p: %p\n", getpid(), p);

    *p = 0; // write to the memory

    while (1) {
        Spin(1);
        *p = *p + 1;    // increment the value pointed to by p
        printf("(%d) p: %d\n", getpid(), *p);
    }

    return 0;

}