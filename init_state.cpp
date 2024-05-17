#include "header/snake_game.h"

// 헤더파일에 선언한 변수들 정의
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

void initScreen() {
    initscr();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    gameSpeed = 100000;
}

void initSnake() {
    // 스네이크 초기 설정
    snakeLength = 3;
    snakeX[0] = SCREEN_WIDTH / 2;
    snakeY[0] = SCREEN_HEIGHT / 2;
}

void initFood() {
    foodX = rand() % (SCREEN_WIDTH - 2) + 1;
    foodY = rand() % (SCREEN_HEIGHT - 2) + 1;
}

void initPoison() {
    poisonX = rand() % (SCREEN_WIDTH - 2) + 1;
    poisonY = rand() % (SCREEN_HEIGHT - 2) + 1;
}
