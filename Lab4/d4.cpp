#include <stdio.h>
#include <stdlib.h>

long factorial(long n) {
    if (n == 0 || n == 1) {
        return 1;
    }
    return n * factorial(n - 1);
}

int main() {
    long result = factorial(5);
    printf("%ld\n", result);
}