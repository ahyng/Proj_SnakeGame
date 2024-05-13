#include "header/snake_game.h"

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
}

void initFood() {
    foodX = rand() % (SCREEN_WIDTH - 2) + 1;
    foodY = rand() % (SCREEN_HEIGHT - 2) + 1;
}
