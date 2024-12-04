#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int height, width;
int ret = 0;

#define RED "\x1b[0;31m"
#define GREEN "\x1b[0;32m"
#define YELLOW "\x1b[0;33m"
#define BLUE "\x1b[0;34m"
#define CYAN "\x1b[0;36m"
#define RESET "\x1b[0;0m"

void draw(int sx, int sy, int dx, int dy, int lim, char* data) {
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            if (x == sx && y == sy) {
                if (!lim) {
                    printf(RED"%c"RESET, data[y*width+x]);
                    sx = width;
                } else {
                    printf(BLUE"%c"RESET, data[y*width+x]);
                    --lim;
                    sx += dx;
                    sy += dy;
                }
            } else {
                printf("%c", data[y*width+x]);
            }
        }
        printf("\n");
    }
    printf("---------------------------\n");
}

void check(int sx, int sy, int dx, int dy, char* data) {
    int x, y;
    for (int i = 1; i < 4; ++i) {
        x = sx + i*dx;
        y = sy + i*dy;

        if (x < 0 || x >= width || y < 0 || y >= height) return;

        if (i == 1 && data[y*width+x] == 'M') continue;
        if (i == 2 && data[y*width+x] == 'A') continue;
        if (i == 3 && data[y*width+x] == 'S') continue;
        /* draw(sx, sy, dx, dy, i+1, data); */
        return;
    }
    /* draw(sx, sy, dx, dy, 3, data); */
    ++ret;
}

int main(int argc, char** argv) {
    if (argc < 3) return 0;

    height = atoi(argv[1]);
    width = atoi(argv[2])-1;

    char data[height*width];
    char temp;
    for (int i = 0; i < height; ++i) {
        fread(&data[i*width], sizeof(char), width, stdin);
        fread(&temp, sizeof(char), 1, stdin);
    }

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            if (data[y*width+x] != 'X') continue;

            check(x, y, 1, 0, data);
            check(x, y, -1, 0, data);
            check(x, y, 0, 1, data);
            check(x, y, 0, -1, data);

            check(x, y, 1, -1, data);
            check(x, y, -1, 1, data);
            check(x, y, 1, 1, data);
            check(x, y, -1, -1, data);
        }
    }

    printf("%d\n", ret);

    return 0;
}
