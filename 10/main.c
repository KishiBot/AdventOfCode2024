#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

#define RED "\x1b[0;31m"
#define GREEN "\x1b[0;32m"
#define YELLOW "\x1b[0;33m"
#define BLUE "\x1b[0;34m"
#define CYAN "\x1b[0;36m"
#define RESET "\x1b[0;0m"

const int width = 1000;
const int height = 1000;

list_t* list;

uint8_t rules[1000*1000];
int line[64];
int ordered[64];

int getMedian(int size) {
    int median = line[size/2];
    for (int i = size-1; i > 0; --i) {
        for (int j = i-1; j >= 0; --j) {
            if (rules[line[i]*width+line[j]]) return 0;
        }
    }
    return median;
}

int getIncorrectMedian(int size) {
    list_clear(list);
    pair_t temp;

    for (int i = 0; i < size; ++i) {
        temp.a = line[i];
        temp.b = 0;
        for (int j = 0; j < size; ++j) {
            if (rules[line[j]*width+temp.a]) ++temp.b;
        }
        list_push(list, temp);
    }

    for (int i = 0; i < list->size; ++i) {
        if (list->data[i].b == size/2) return list->data[i].a;
    }
    return 0;
}

int main(int argc, char** argv) {
    memset(rules, 0, sizeof(rules));
    memset(line, 0, sizeof(line));
    list = list_create(48);

    int a, b;
    int ret = 0;
    while (scanf("%d|%d\n", &a, &b) == 2) {
        rules[a*width+b] = 1;
    }

    line[0] = a;
    int size = 0;
    while (scanf(",%d", &a) == 1) {
        line[++size] = a;
    }
    size+=1;
    int m = getMedian(size);
    if (!m) ret += getIncorrectMedian(size);

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
        if (size == 1) continue;

        int m = getMedian(size);
        if (!m) ret += getIncorrectMedian(size);
    }
    printf("%d\n", ret);

    list_destroy(list);
}
