#include <stdint.h>
#include <stdio.h>
#include <string.h>

uint64_t size = 0;
uint64_t line[64];
char temp[1024];

uint8_t check(uint64_t a, uint64_t idx, uint64_t sum) {
    if (idx == size && sum == a) return 1;
    else if (idx == size && sum != a) return 0;

    uint64_t s = sum + line[idx];
    if (check(a, idx+1, s)) return 1;
    s = sum * line[idx];
    if (check(a, idx+1, s)) return 1;

    memset(temp, 0, sizeof(temp));
    sprintf(temp, "%lu", line[idx]);
    s = sum;
    for (int i = 0; temp[i] != '\0'; ++i) {
        s = s * 10 + temp[i]-48;
    }

    if (check(a, idx+1, s)) return 1;

    return 0;
}

int main() {
    uint64_t a;
    uint64_t ret = 0;

    char ch;
    uint64_t num = 0;;
    while (scanf("%c", &ch) == 1) {
        if (ch == '\n') {
            line[size-1] = num;
            if (check(a, 1, line[0])) ret += a;
            num = 0;
            size = 0;
        } else if (ch == ' ') {
            if (size == 0) {
                a = num;
                ++size;
            } else line[(size++)-1] = num;
            num = 0;
        } else {
            num = num*10+ch-48;
        }
    }

    printf("%lu\n", ret);

    return 0;
}
