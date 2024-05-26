#include "header/snake_game.h"

int wall[NUM_WALL][2];

void drawScreen() {
    // 화면 클리어
    clear();

    int index = 0;
    // 네모 그리기 Stage1
    for (int i = 0; i < SCREEN_WIDTH; ++i) {
        mvaddch(0, i, '#'); // 윗면
        mvaddch(SCREEN_HEIGHT - 1, i, '#'); // 아랫면
    }
    for (int i = 0; i < SCREEN_HEIGHT; ++i) {
        mvaddch(i, 0, '#'); // 왼쪽면
        mvaddch(i, SCREEN_WIDTH - 1, '#'); // 오른쪽면
    }

    // 장애물 위치 Stage2
    // 아직 점수가 구현되지 않았으므로 조건문 미포함
    // 윗면
    for (int i = -10; i <= 9; ++i) {
        wall[index][0] = SCREEN_HEIGHT / 2 - 4;
        wall[index][1] = SCREEN_WIDTH / 2 + i;
        ++index;
    }

    // 왼쪽면
    for (int i = -3; i <= 3; ++i) {
        wall[index][0] = SCREEN_HEIGHT / 2 + i;
        wall[index][1] = SCREEN_WIDTH / 2 - 10;
        ++index;
    }

    // 아랫면
    for (int i = -9; i <= 9; ++i) {
        wall[index][0] = SCREEN_HEIGHT / 2 + 3;
        wall[index][1] = SCREEN_WIDTH / 2 + i;
        ++index;
    }

    // 장애물 그리기 Stage2
    for (int i = 0; i < 48; ++i) {
        mvaddch(wall[i][0], wall[i][1], '#');
    }

    // 먹이 그리기
    mvaddch(foodY, foodX, '@');

    // 독 그리기
    mvaddch(poisonY, poisonX, '%');

    // 더블 그리기
    mvaddch(doubleY, doubleX, '&');


    // 스네이크 그리기
    for (int i = 0; i < snakeLength; ++i) {
        mvaddch(snakeY[i], snakeX[i], 'O');
    }
    // 게이트 그리기
    if (gateCondition) {
        mvaddch(gate1.first, gate1.second, 'G'); // 첫 번째 게이트
        mvaddch(gate2.first, gate2.second, 'G'); // 두 번째 게이트
    }

    refresh(); // 화면 업데이트
}
