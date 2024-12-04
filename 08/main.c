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

void draw(int tx, int ty, char* data) {
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int pos = y*width+x;
            if (x == tx && y == ty) printf(BLUE"%c"RESET, data[pos]);
            else if ((x == tx-1 || x == tx+1) && (y == ty-1 || y == ty+1)) printf(YELLOW"%c"RESET, data[pos]);
            else if ((x == tx -1 || x == tx + 1 || x == tx) && (y == ty || y == ty - 1 || y == ty + 1))printf("%c", data[pos]);
            if (x == tx + 1 && (y == ty || y == ty-1 || y == ty+1)) printf("\n");
        }
    }
    printf("--------------------------\n");
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

    for (int y = 1; y < height; ++y) {
        for (int x = 1; x < width; ++x) {
            if (x == width-1 || y == height-1) continue;
            if (data[y*width+x] != 'A') continue;

            if (data[(y-1)*width+x-1] == 'M' && data[(y+1)*width+x+1] != 'S') continue;
            if (data[(y-1)*width+x-1] == 'S' && data[(y+1)*width+x+1] != 'M') continue;

            if (data[(y-1)*width+x+1] == 'M' && data[(y+1)*width+x-1] != 'S') continue;
            if (data[(y-1)*width+x+1] == 'S' && data[(y+1)*width+x-1] != 'M') continue;

            if (data[(y-1)*width+x-1] == 'X' || data[(y+1)*width+x+1] == 'X' ||
                data[(y-1)*width+x+1] == 'X'  || data[(y+1)*width+x-1] == 'X') continue;
            if (data[(y-1)*width+x-1] == 'A' || data[(y+1)*width+x+1] == 'A' ||
                data[(y-1)*width+x+1] == 'A'  || data[(y+1)*width+x-1] == 'A') continue;

            /* draw(x, y, data); */
            ++ret;
        }
    }

    printf("%d\n", ret);

    return 0;
}
