#include "header/snake_game.h"

void drawScreen() {
    // 화면 클리어
    clear();

    // 네모 그리기
    for (int i = 0; i < SCREEN_WIDTH; ++i) {
        mvaddch(0, i, '#'); // 윗면
        mvaddch(SCREEN_HEIGHT - 1, i, '#'); // 아랫면
    }
    for (int i = 0; i < SCREEN_HEIGHT; ++i) {
        mvaddch(i, 0, '#'); // 왼쪽면
        mvaddch(i, SCREEN_WIDTH - 1, '#'); // 오른쪽면
    }

    // 먹이 그리기
    mvaddch(foodY, foodX, '@');

    // 독 그리기
    mvaddch(poisonY, poisonX, '%');

    // 스네이크 그리기
    for (int i = 0; i < snakeLength; ++i) {
        mvaddch(snakeY[i], snakeX[i], 'O');
    }

    refresh(); // 화면 업데이트
}