#ifndef SNAKE_GAME_H
#define SNAKE_GAME_H

#include <ncurses.h>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <unistd.h>

#define SCREEN_WIDTH 50
#define SCREEN_HEIGHT 20
#define MAX_LENGTH 100

extern int snakeX[MAX_LENGTH];
extern int snakeY[MAX_LENGTH];
extern int snakeLength;
extern int direction;
extern int gameSpeed;
extern std::mutex mtx;
extern std::condition_variable cv;
extern bool game_over;
extern int foodX, foodY;

void initScreen();
void initSnake();
void initFood();
void drawScreen();
void moveSnake();
void handleInput();
void runGame();
void game_start();

#endif
