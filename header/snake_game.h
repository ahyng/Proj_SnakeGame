#ifndef SNAKE_GAME_H
#define SNAKE_GAME_H

using namespace std;

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

#define INNER_TOP (20 / 4)
#define INNER_BOTTOM (3 * 20 / 4)
#define INNER_LEFT (50 / 4)
#define INNER_RIGHT (3 * 50 / 4)


extern int snakeX[MAX_LENGTH];
extern int snakeY[MAX_LENGTH];
extern int snakeLength;
extern int direction;
extern int gameSpeed;
extern std::mutex mtx;
extern std::condition_variable cv;
extern bool game_over;
extern int foodX, foodY;
extern int poisonX, poisonY;
extern int portal1X, portal1Y;
extern int portal2X, portal2Y;
extern int inner_top, inner_bottom, inner_left, inner_right;


void initScreen();
void initSnake();
void initFood();
void initPoison();
void drawScreen();
void moveSnake();
void handleInput();
void runGame();
void game_start();
void initPortals();

#endif
