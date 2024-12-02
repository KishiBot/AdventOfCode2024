#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv) {
    int a = -1, b = -1;
    int n = 0;
    uint8_t descend = 0;
    uint8_t safe = 1;
    int safeCount = 0;

    char* line = malloc(sizeof(char)*1024);
    size_t size = 1024*sizeof(char);

    while (getline(&line, &size, stdin) != EOF) {
        for (int i = 0; line[i] != '\0'; ++i) {
            if (line[i] == ' ' || line[i] == '\n') {
                if (a == -1) {
                    a = n;
                    n = 0;
                    continue;
                } else if (b == -1) {
                    b = n;
                    n = 0;
                    if (a == b || abs(a-b) > 3) {
                        safe = 0;
                        break;
                    }

                    descend = a > b ? 1 : 0;
                    continue;
                }

                a = b;
                b = n;
                n = 0;

                if (descend && a <= b) {
                    safe = 0;
                    break;
                } else if (!descend && a >= b) {
                    safe = 0;
                    break;
                } else if (abs(a-b) > 3) {
                    safe = 0;
                    break;
                }
            } else {
                n = n*10+line[i]-48;
            }
        }

        a = -1;
        b = -1;
        if (safe) ++safeCount;
        safe = 1;
    }

    printf("%d\n", safeCount);

    return 0;
}
