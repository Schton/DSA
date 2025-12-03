#include <stdio.h>

int factorial(int n) {
    if (n == 0 || n == 1) {
        return 1; // Base case
    }
    return n * factorial(n - 1); // Recursive step
}

int main(){
    int n;
    printf("%d", n = factorial(10));
    return 0;
}