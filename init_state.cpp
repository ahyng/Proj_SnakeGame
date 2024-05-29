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
int portal1X, portal1Y;
int portal2X, portal2Y;

void initScreen() {
    initscr();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    gameSpeed = 100000;
    srand(time(0)); // Random seed initialization
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

void initFood() {
    do {
        foodX = rand() % (SCREEN_WIDTH - 2) + 1;
        foodY = rand() % (SCREEN_HEIGHT - 2) + 1;
    } while ((foodX >= INNER_LEFT && foodX <= INNER_RIGHT && (foodY == INNER_TOP || foodY == INNER_BOTTOM)) ||
             (foodY >= INNER_TOP && foodY <= INNER_BOTTOM && (foodX == INNER_LEFT || foodX == INNER_RIGHT)));
}

void initPoison() {
    do {
        poisonX = rand() % (SCREEN_WIDTH - 2) + 1;
        poisonY = rand() % (SCREEN_HEIGHT - 2) + 1;
    } while ((foodX >= INNER_LEFT && foodX <= INNER_RIGHT && (foodY == INNER_TOP || foodY == INNER_BOTTOM)) ||
             (foodY >= INNER_TOP && foodY <= INNER_BOTTOM && (foodX == INNER_LEFT || foodX == INNER_RIGHT)));
}

