#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int main() {
    printf("hello\n");
    // kill(getpid(), 9);
    // raise(9);
    abort();
    printf("world");

    return 0;
}