#include "header/snake_game.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

std::chrono::steady_clock::time_point lastPortalsTime;


// 포탈이 특정 위치에 생성되지 않도록 하는 함수
bool isExcludedPosition(int x, int y) {
    return (x == 0 && y == 0) || 
           (x == SCREEN_WIDTH - 1 && y == 0) || 
           (x == 0 && y == SCREEN_HEIGHT - 1) || 
           (x == SCREEN_WIDTH - 1 && y == SCREEN_HEIGHT - 1) ||
           (x == 12 && y == 7) || 
           (x == SCREEN_WIDTH - 12 && y == 7) || 
           (x == 12 && y == SCREEN_HEIGHT - 6) || 
           (x == SCREEN_WIDTH - 12 && y == SCREEN_HEIGHT - 6);
}

void initPortals() {
    // 랜덤 시드 설정
    srand(time(0));

    // 포탈 위치 설정을 위해 맵을 그립니다.
    drawScreen();

    // '#'이 있는 곳에 포탈을 생성합니다.
    do {
        portal1X = rand() % SCREEN_WIDTH;
        portal1Y = rand() % SCREEN_HEIGHT;
    } while (mvinch(portal1Y, portal1X) != '#' || isExcludedPosition(portal1X, portal1Y));

    do {
        portal2X = rand() % SCREEN_WIDTH;
        portal2Y = rand() % SCREEN_HEIGHT;
    } while (mvinch(portal2Y, portal2X) != '#' || 
             isExcludedPosition(portal2X, portal2Y) || 
             (portal1X == portal2X && portal1Y == portal2Y));

    lastPortalsTime = std::chrono::steady_clock::now();
}




void updatePortals(){
    while (!game_over) {
        std::this_thread::sleep_for(std::chrono::seconds(1));

        std::unique_lock<std::mutex> lk(mtx);
        auto now = std::chrono::steady_clock::now();

        if (std::chrono::duration_cast<std::chrono::seconds>(now - lastPortalsTime).count() >= 5) {
            initPortals();
        }

        lk.unlock(); // 필요에 따라 수동으로 언락 가능

        cv.notify_all();
    }
}