#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv) {
    int a = -1, b = -1;
    int n = 0;
    int8_t descend = -1;
    uint8_t safe = 1;
    int safeCount = 0;
    uint8_t removed = 0;

    char* line = malloc(sizeof(char)*1024);
    size_t s = 1024*sizeof(char);

    int temp[8];
    memset(temp, 0, sizeof(temp));
    int size = 0;

    int idx = 0;
    while (getline(&line, &s, stdin) != EOF) {
        for (int i = 0; line[i] != '\0'; ++i) {
            if (line[i] == ' ' || line[i] == '\n') {
                temp[size++] = n;
                n = 0;
            } else {
                n = n*10+line[i]-48;
            }
        }

        for (int i = 0; i < size; ++i) {
            uint8_t safe = 1;

            int a = i != 0 ? temp[0] : temp[1];
            int b = i > 1 ? temp[1] : temp[2];
            descend = a > b ? 1 : 0;

            for (int j = 0; j < size-1; ++j) {
                if (j == i) continue;
                int next = j+1 != i ? j+1 : j+2;
                if (next == size) break;

                if (descend && temp[j] <= temp[next]) {
                    safe = 0;
                    break;
                } else if (!descend && temp[j] >= temp[next]) {
                    safe = 0;
                    break;
                } else if (abs(temp[j] - temp[next]) > 3) {
                    safe = 0;
                    break;
                }
            }

            if (safe) {
                ++safeCount;
                break;
            }
        }

        size = 0;
    }

    printf("%d\n", safeCount);
    return 0;
}
