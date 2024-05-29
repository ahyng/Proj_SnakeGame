#include "header/snake_game.h"

void drawScreen() {
    // 화면 클리어
    clear();

    drawMap(mapState);

    // 먹이 그리기
    mvaddch(foodY, foodX, '@');

    // 독 그리기
    mvaddch(poisonY, poisonX, '%');

    // 스네이크 그리기
    for (int i = 0; i < snakeLength; ++i) {
        mvaddch(snakeY[i], snakeX[i], 'O');
    }

    // 포탈 그리기
    mvaddch(portal1Y, portal1X, 'G');
    mvaddch(portal2Y, portal2X, 'G');

    refresh(); // 화면 업데이트
}