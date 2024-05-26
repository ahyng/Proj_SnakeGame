#ifndef SNAKE_GAME_H
#define SNAKE_GAME_H

#include <ncurses.h>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <unistd.h>
#include <chrono>
#include <thread>

#define SCREEN_WIDTH 50
#define SCREEN_HEIGHT 20
#define MAX_LENGTH 100
#define NUM_WALL 48

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
extern int doubleX, doubleY;
extern std::chrono::steady_clock::time_point lastFoodTime;
extern std::chrono::steady_clock::time_point lastPoisonTime;
extern std::chrono::steady_clock::time_point lastDoubleTime;
extern bool doubleActive;
extern std::chrono::steady_clock::time_point doubleStartTime;
extern std::pair<int, int> gate1;
extern std::pair<int, int> gate2;
extern std::mutex mtxG;
extern bool gateCondition;
extern int wall[NUM_WALL][2];

void initScreen();
void initSnake();
bool itemPosition(int x, int y);
void initFood();
void initPoison();
void initDouble();
void updateItem();
void drawScreen();
void moveSnake();
void generateGate();
void updateGate();
void checkGateCollision();
void handleInput();
void runGame();
void game_start();

#endif
