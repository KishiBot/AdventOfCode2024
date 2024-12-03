#include <stdint.h>
#include <stdio.h>

int main() {
    int res = 0;
    int a, b;

    while (scanf("%d,%d\n", &a, &b) == 2) {
        res += a*b;
    }
    printf("%d\n", res);
}
