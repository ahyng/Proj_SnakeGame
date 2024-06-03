#include "header/snake_game.h"

void resetGame() {
    game_over = true;
    mvprintw(SCREEN_HEIGHT / 2 - 1, SCREEN_WIDTH / 2 - 5, "Game Over");
    mvprintw(SCREEN_HEIGHT / 2, SCREEN_WIDTH / 2 - 12, "Press any key to restart");
    refresh();
    getch();
    game_over = false;
    srand(time(0)); // Re-seed the random number generator for each restart
    initSnake();
    initFood();
    initPoison();
    initPortals();
    score = 0;  // 점수 초기화
    foodEaten = 0;  // 먹은 먹이 수 초기화
    mapState = 1; // 맵 상태를 1로 설정
}