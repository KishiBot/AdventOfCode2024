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

int width, height;

void print(uint8_t* data, uint8_t* visited, int posX, int posY) {
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            if (data[y*width+x]) printf("#");
            else if (x == posX && y == posY) printf(CYAN"o"RESET);
            else if (visited[y*width+x]) printf(BLUE"%%"RESET);
            else printf(".");
        }
        printf("\n");
    }
    printf("---------------------------------\n");
}

int main(int argc, char** argv) {
    if (argc < 3) return 0;

    height = atoi(argv[1]);
    width = atoi(argv[2])-1;

    int posX = 0;
    int posY = 0;

    int dirX = 0;
    int dirY = -1;

    uint8_t data[height*width];
    uint8_t visited[height*width];
    memset(data, 0, sizeof(data));
    memset(visited, 0, sizeof(visited));

    char temp[width+1];
    for (int y = 0; y < height; ++y) {
        fread(temp, sizeof(char), width+1, stdin);
        for (int x = 0; x < width; ++x) {
            if (temp[x] == '#') {
                data[y*width+x] = 1;
            } else if (temp[x] == '^') {
                posX = x;
                posY = y;
            }
        }
    }

    int ret = 1;
    visited[posY*width+posX] = 1;

    while (1) {
        int newPos = (posY+dirY)*width+posX+dirX;
        if (newPos < 0 || newPos >= width*height) break;

        if (data[newPos]) {
            if (dirX == 0 && dirY == -1) {
                dirX = 1;
                dirY = 0;
            } else if (dirX == 1 && dirY == 0) {
                dirX = 0;
                dirY = 1;
            } else if (dirX == 0 && dirY == 1) {
                dirX = -1;
                dirY = 0;
            } else {
                dirX = 0;
                dirY = -1;
            }
        } else {
            posX += dirX;
            posY += dirY;
            if (!visited[newPos]) ++ret;
            visited[newPos] = 1;
            /* print(data, visited, posX, posY); */
        }
    }

    printf("%d\n", ret);

    return 0;
}
