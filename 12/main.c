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

uint8_t getLastPos(uint8_t* data, uint8_t* visited, int posX, int posY, int dirX, int dirY, int tx, int ty) {
    int checkX = -1;
    int checkY = -1;
    int i = 0;
    while (1) {
        ++i;
        if (visited[(posY+dirY)*width+posX+dirX] >= 4) return 1;
        if (posX+dirX == tx && posY+dirY == ty && checkX == -1) {
            checkX = posX;
            checkY = posY;
        }

        if (posX+dirX < 0 || posX+dirX >= width || posY+dirY < 0 || posY+dirY >= height) return 0;
        int newPos = (posY+dirY)*width+posX+dirX;

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
            visited[posY*width+posX] += 1;
        }
    }
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
    uint8_t visitedData[height*width];
    memset(data, 0, sizeof(data));
    memset(visited, 0, sizeof(visited));
    memset(visitedData, 0, sizeof(visitedData));

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

    visitedData[posY*width+posX] = 1;
    visited[posY*width+posX] = 1;

    int ret = 0;
    getLastPos(data, visitedData, posX, posY, dirX, dirY, -1, -1);
    int i = 0;
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            if (x == posX && y == posY) continue;
            if (visitedData[y*width+x]) {
                data[y*width+x] = 1;

                memset(visited, 0, sizeof(visited));
                visited[posY*width+posX] = 1;

                ret += getLastPos(data, visited, posX, posY, dirX, dirY, x, y);
                data[y*width+x] = 0;
            }
        }
    }

    printf("%d\n", ret);

    return 0;
}
