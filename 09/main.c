#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RED "\x1b[0;31m"
#define GREEN "\x1b[0;32m"
#define YELLOW "\x1b[0;33m"
#define BLUE "\x1b[0;34m"
#define CYAN "\x1b[0;36m"
#define RESET "\x1b[0;0m"

const int width = 1000;
const int height = 1000;

uint8_t rules[1000*1000];
int line[64];

int getMedian(int size) {
    int median = line[size/2];
    for (int i = size-1; i > 0; --i) {
        for (int j = i-1; j >= 0; --j) {
            if (rules[line[i]*width+line[j]]) return 0;
        }
    }
    return median;
}

int main(int argc, char** argv) {
    memset(rules, 0, sizeof(rules));
    memset(line, 0, sizeof(line));

    int a, b;
    int ret = 0;
    while (scanf("%d|%d\n", &a, &b) == 2) {
        rules[a*width+b] = 1;
    }

    int idx = 0;
    line[0] = a;
    int size = 0;
    while (scanf(",%d", &a) == 1) {
        line[++size] = a;
    }
    size+=1;
    ret += getMedian(size);
    for (int i = 0; i < size; ++i) {
        printf("%d,", line[i]);
    }
    printf(": %d\n", getMedian(size));
    idx+=1;

    char ch = 0;
    while (size > 0) {
        size = 0;
        a = 0;
        while (scanf("%c", &ch) == 1) {
            if (ch == '\n') {
                line[size++] = a;
                break;
            } else if (ch == ',') {
                line[size++] = a;
                a = 0;
            } else {
                a = a*10+ch-48;
            }
        }
        if (!size) break;

        ret += getMedian(size);
        for (int i = 0; i < size; ++i) {
            printf("%d,", line[i]);
        }
        printf(": %d\n", getMedian(size));
        idx+=1;
    }
    printf("%d\n", ret);
}
