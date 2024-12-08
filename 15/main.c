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

#define capacity 8

typedef struct {
    int x;
    int y;
} pos_t;

pos_t numPos[10*capacity];
pos_t lowerPos[26*capacity];
pos_t higherPos[26*capacity];
int numSize[10];
int lowerSize[26];
int higherSize[26];

int width, height;

int main(int argc, char** argv) {
    if (argc < 3) return 1;

    height = atoi(argv[1]);
    width = atoi(argv[2])-1;

    char data[width*height];
    memset(data, 0, sizeof(data));

    uint8_t map[width*height];
    memset(map, 0, sizeof(map));

    char ch;
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width+1; ++x) {
            scanf("%c", &ch);
            if (ch == '\n') continue;
            if (ch != '.') data[y*width+x] = ch;
            if (ch >= 48 && ch <= 57) {
                // nums
                ch -= 48;
                numPos[ch*capacity+numSize[ch]].x = x;
                numPos[ch*capacity+numSize[ch]++].y = y;
            } else if (ch >= 65 && ch <= 90) {
                // higher
                ch -= 65;
                higherPos[ch*capacity+higherSize[ch]].x = x;
                higherPos[ch*capacity+higherSize[ch]++].y = y;
            } else if (ch >= 97 && ch <= 122) {
                // lower
                ch -= 97;
                lowerPos[ch*capacity+lowerSize[ch]].x = x;
                lowerPos[ch*capacity+lowerSize[ch]++].y = y;
            }
        }
    }

    for (int num = 0; num < 10; ++num) {
        for (int i = 0; i < numSize[num]; ++i) {
            for (int j = 0; j < numSize[num]; ++j) {
                if (j == i) continue;
                pos_t a = numPos[num*capacity+i];
                pos_t b = numPos[num*capacity+j];

                pos_t pos = {
                    a.x - (b.x - a.x),
                    a.y - (b.y - a.y),
                };

                if (pos.x < 0 || pos.x >= width || pos.y < 0 || pos.y >= height) continue;
                map[pos.y*width+pos.x] = 1;

                /* for (int y = 0; y < height; ++y) { */
                /*     for (int x = 0; x < width; ++x) { */
                /*         int _pos = y*width+x; */
                /*         if (x == a.x && y == a.y) printf(BLUE); */
                /*         else if (x == b.x && y == b.y) printf(GREEN); */
                /*         else if (x == pos.x && y == pos.y) printf(RED); */
                /*         if (data[_pos]) printf("%c", data[_pos]); */
                /*         else printf("%s", map[_pos] ? "#" : "."); */
                /*         printf(RESET); */
                /*     } */
                /*     printf("\n"); */
                /* } */
                /* printf("\n\n\n"); */
            }
        }
    }
    for (int higher = 0; higher < 26; ++higher) {
        for (int i = 0; i < higherSize[higher]; ++i) {
            for (int j = 0; j < higherSize[higher]; ++j) {
                if (j == i) continue;
                pos_t a = higherPos[higher*capacity+i];
                pos_t b = higherPos[higher*capacity+j];

                pos_t pos = {
                    a.x - (b.x - a.x),
                    a.y - (b.y - a.y),
                };

                if (pos.x < 0 || pos.x >= width || pos.y < 0 || pos.y >= height) continue;
                map[pos.y*width+pos.x] = 1;
            }
        }
    }
    for (int lower = 0; lower < 26; ++lower) {
        for (int i = 0; i < lowerSize[lower]; ++i) {
            for (int j = 0; j < lowerSize[lower]; ++j) {
                if (j == i) continue;
                pos_t a = lowerPos[lower*capacity+i];
                pos_t b = lowerPos[lower*capacity+j];

                pos_t pos = {
                    a.x - (b.x - a.x),
                    a.y - (b.y - a.y),
                };

                if (pos.x < 0 || pos.x >= width || pos.y < 0 || pos.y >= height) continue;
                map[pos.y*width+pos.x] = 1;
            }
        }
    }

    int ret = 0;
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            if (map[y*width+x]) ++ret;
        }
    }
    printf("%d\n", ret);
}
