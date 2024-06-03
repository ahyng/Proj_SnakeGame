#ifndef SNAKE_GAME_H
#define SNAKE_GAME_H

using namespace std;

#include <iostream>
#include <ncurses.h>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <unistd.h>
#include <vector>
#include <utility>
#include <chrono>

#define SCREEN_WIDTH 50
#define SCREEN_HEIGHT 20
#define MAX_LENGTH 14
#define NUM_WALL 48

#define INNER_TOP (20 / 4)
#define INNER_BOTTOM 6
#define INNER_LEFT (50 / 4)
#define INNER_RIGHT SCREEN_HEIGHT - 6


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
extern bool doubleActive;
extern std::chrono::steady_clock::time_point lastFoodTime;
extern std::chrono::steady_clock::time_point lastPoisonTime;
extern std::chrono::steady_clock::time_point lastDoubleTime;
extern std::chrono::steady_clock::time_point doubleStartTime;
extern int portal1X, portal1Y;
extern int portal2X, portal2Y;
extern int inner_top, inner_bottom, inner_left, inner_right;
extern std::chrono::steady_clock::time_point lastPortalsTime;
extern int growthItemCount;
extern int poisonItemCount;
extern int gateCount;
extern std::chrono::steady_clock::time_point gameStartTime;
extern int wall[NUM_WALL][2];
extern int score;           // 점수 변수 추가
extern int mapState;        // 맵 상태 변수 추가
extern int foodEaten;  // 먹이를 먹은 횟수를 추적하는 변수

void initScreen();
void initSnake();
void initFood();
void initPoison();
void initDouble();
void updateItem();
void drawScreen();
void drawMap(int mapState);  // 맵 상태 인자를 받도록 수정
void moveSnake();
void handleInput();
void runGame();
void game_start();
void resetGame();
void initPortals();
void updatePortals();
bool isExcludedPosition();
bool checkConditionToChangeMap();
void waitForUserInput();

#endif