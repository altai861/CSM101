#include <stdio.h>
#include <stdlib.h>

int x = 5;

void foo() {
    int y = 10;
    printf("%i\n", x + y);
}

void bar() {
    x = 7;
    foo();
}

int main() {
    bar();
    printf("%i\n", x);
}