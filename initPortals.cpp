#include "header/snake_game.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

void initPortals() {
    // 랜덤 시드 설정
    srand(time(0));

    // 포탈 위치 설정
    int side;
    do {
        side = rand() % 4; // 0: top, 1: bottom, 2: left, 3: right
        switch (side) {
            case 0: // top
                portal1X = rand() % (SCREEN_WIDTH - 2) + 1;
                portal1Y = 0;
                break;
            case 1: // bottom
                portal1X = rand() % (SCREEN_WIDTH - 2) + 1;
                portal1Y = SCREEN_HEIGHT - 1;
                break;
            case 2: // left
                portal1X = 0;
                portal1Y = rand() % (SCREEN_HEIGHT - 2) + 1;
                break;
            case 3: // right
                portal1X = SCREEN_WIDTH - 1;
                portal1Y = rand() % (SCREEN_HEIGHT - 2) + 1;
                break;
        }
        
        side = rand() % 4; // 0: top, 1: bottom, 2: left, 3: right
        switch (side) {
            case 0: // top
                portal2X = rand() % (SCREEN_WIDTH - 2) + 1;
                portal2Y = 0;
                break;
            case 1: // bottom
                portal2X = rand() % (SCREEN_WIDTH - 2) + 1;
                portal2Y = SCREEN_HEIGHT - 1;
                break;
            case 2: // left
                portal2X = 0;
                portal2Y = rand() % (SCREEN_HEIGHT - 2) + 1;
                break;
            case 3: // right
                portal2X = SCREEN_WIDTH - 1;
                portal2Y = rand() % (SCREEN_HEIGHT - 2) + 1;
                break;
        }
    } while ((portal1X == portal2X && portal1Y == portal2Y) || // 서로 다른 위치
             (abs(portal1X - portal2X) <= 1 && portal1Y == portal2Y) || 
             (abs(portal1Y - portal2Y) <= 1 && portal1X == portal2X));
} 