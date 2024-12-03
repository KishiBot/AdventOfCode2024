#include <stdint.h>
#include <stdio.h>

int main() {
    int res = 0;
    int a;
    int n = 0;
    char ch;
    uint8_t first = 1;
    uint8_t ignore = 0;

    while (scanf("%c", &ch) == 1) {
        if (ch == 'd') {
            ignore = 0;
        } else if (ch == 'n') {
            ignore = 1;
        } else if (ch == '\n' && !ignore) {
            first = 1;
            res += a*n;
            n = 0;
        } else if (ch == ',' && !ignore) {
            first = 0;
            a = n;
            n = 0;
        } else if (!ignore) {
            n = n*10+ch-48;
        }
    }

    printf("%d\n", res);
}
