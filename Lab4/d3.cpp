#include <stdio.h>
#include <stdlib.h>

int x = 5;

void foo() {
    printf("%i\n", x);
}

void bar() {
    x = 10;
    foo();
}

int main() {
    bar();
}