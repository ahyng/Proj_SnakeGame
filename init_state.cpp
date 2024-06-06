#include "header/snake_game.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

int snakeX[MAX_LENGTH];
int snakeY[MAX_LENGTH];
int snakeLength;
int direction;
int gameSpeed;
std::mutex mtx;
std::condition_variable cv;
bool game_over;
int foodX, foodY;
int poisonX, poisonY;
int doubleX, doubleY;
bool doubleActive = false;
std::chrono::steady_clock::time_point lastFoodTime;
std::chrono::steady_clock::time_point lastPoisonTime;
std::chrono::steady_clock::time_point lastDoubleTime;
std::chrono::steady_clock::time_point doubleStartTime;
int portal1X, portal1Y;
int portal2X, portal2Y;
int growthItemCount = 0;
int poisonItemCount = 0;
int gateCount = 0;
std::chrono::steady_clock::time_point gameStartTime;


void initScreen() {
    initscr();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    gameSpeed = 100000;
}

void initSnake() {
    snakeLength = 3;
    snakeX[0] = SCREEN_WIDTH / 2;
    snakeY[0] = SCREEN_HEIGHT / 2;
    for (int i = 1; i < snakeLength; ++i) {
        snakeX[i] = snakeX[0] - i;
        snakeY[i] = snakeY[0];
    }
    direction = KEY_RIGHT;
}

bool isValidPosition(int x, int y) {
    // 벽과 겹치는지 확인
    if ((x >= INNER_LEFT && x <= INNER_RIGHT) && (y <= INNER_TOP || y >= INNER_BOTTOM)) {
        return false; 
    }
    // 벽 위에 있는지 확인
    if (mvinch(y, x) == '#') {
        return false;
    }
    
    return true;
}

void initFood() {
    do {
        foodX = rand() % (SCREEN_WIDTH - 2) + 1;
        foodY = rand() % (SCREEN_HEIGHT - 2) + 1;
    } while (!isValidPosition(foodX, foodY));{
        lastFoodTime = std::chrono::steady_clock::now();
    }
}

void initPoison() {
    do {
        poisonX = rand() % (SCREEN_WIDTH - 2) + 1;
        poisonY = rand() % (SCREEN_HEIGHT - 2) + 1;
    } while (!isValidPosition(poisonX, poisonY));{
        lastPoisonTime = std::chrono::steady_clock::now();
    }
}

void initDouble() {
    do {
        doubleX = rand() % (SCREEN_WIDTH - 2) + 1;
        doubleY = rand() % (SCREEN_HEIGHT - 2) + 1;
    } while (!isValidPosition(doubleX, doubleY));{
        lastDoubleTime = std::chrono::steady_clock::now();
    }
}

void updateItem() {
    while (!game_over) {
        std::this_thread::sleep_for(std::chrono::seconds(1));

        std::unique_lock<std::mutex> lk(mtx);
        auto now = std::chrono::steady_clock::now();

        if (std::chrono::duration_cast<std::chrono::seconds>(now - lastFoodTime).count() >= 5) {
            initFood();
        }
        if (std::chrono::duration_cast<std::chrono::seconds>(now - lastPoisonTime).count() >= 5) {
            initPoison();
        }
        if (std::chrono::duration_cast<std::chrono::seconds>(now - lastDoubleTime).count() >= 5) {
            initDouble();
        }
        lk.unlock();

        cv.notify_all();
    }
}