#include <ncurses.h>
#include "header/snake_game.h"

void drawScreen() {
    clear();

    // 상단 테두리 그리기
    for (int i = 0; i < SCREEN_WIDTH/4; ++i) {
        mvaddch(0, i, '#');
    }

    for (int i = SCREEN_WIDTH/4; i < 3 * SCREEN_WIDTH/4+1; ++i) {
        mvaddch(6, i, '#');
    }

    for (int i =  3 * SCREEN_WIDTH/4; i < SCREEN_WIDTH; ++i) {
        mvaddch(0, i, '#');
    }

    for (int i = 0; i < 6; ++i) {
        mvaddch(i, SCREEN_WIDTH/4, '#');
    }

    for (int i = 0; i < 6; ++i) {
        mvaddch(i, 3 * SCREEN_WIDTH/4, '#');
    }

    // 하단 테두리 그리기
    for (int i = 0; i < SCREEN_WIDTH/4+1; ++i) {
        mvaddch(SCREEN_HEIGHT-1, i, '#');
    }

    for (int i = SCREEN_WIDTH/4; i < 3 * SCREEN_WIDTH/4; ++i) {
        mvaddch(SCREEN_HEIGHT-7, i, '#');
    }

    for (int i =  3 * SCREEN_WIDTH/4; i < SCREEN_WIDTH; ++i) {
        mvaddch(SCREEN_HEIGHT-1, i, '#');
    }

    for (int i = SCREEN_HEIGHT-7; i < SCREEN_HEIGHT-1; ++i) {
        mvaddch(i, SCREEN_WIDTH/4, '#');
    }

    for (int i = SCREEN_HEIGHT-7; i < SCREEN_HEIGHT-1; ++i) {
        mvaddch(i, 3 * SCREEN_WIDTH/4, '#');
    }


    // 좌측 테두리 그리기
    for (int i = 0; i < SCREEN_HEIGHT; ++i) {
        mvaddch(i, 0, '#');
    }
    // 우측 테두리 그리기
    for (int i = 0; i < SCREEN_HEIGHT; ++i) {
        mvaddch(i, SCREEN_WIDTH - 1, '#');
    }

    // 음식 그리기
    mvaddch(foodY, foodX, '@');
    // 독 그리기
    mvaddch(poisonY, poisonX, '%');

    // 뱀 그리기
    for (int i = 0; i < snakeLength; ++i) {
        mvaddch(snakeY[i], snakeX[i], 'O');
    }

    // 포탈 그리기
    mvaddch(portal1Y, portal1X, ' ');
    mvaddch(portal2Y, portal2X, ' ');

    refresh();
}

//이전 코드
// void drawScreen() {
//     // 화면 클리어
//     clear();

//     // 네모 그리기
//     for (int i = 0; i < SCREEN_WIDTH; ++i) {
//         mvaddch(0, i, '#'); // 윗면
//         mvaddch(SCREEN_HEIGHT - 1, i, '#'); // 아랫면
//     }
//     for (int i = 0; i < SCREEN_HEIGHT; ++i) {
//         mvaddch(i, 0, '#'); // 왼쪽면
//         mvaddch(i, SCREEN_WIDTH - 1, '#'); // 오른쪽면
//     }

//     // 먹이 그리기
//     mvaddch(foodY, foodX, '@');

//     // 스네이크 그리기
//     for (int i = 0; i < snakeLength; ++i) {
//         mvaddch(snakeY[i], snakeX[i], 'O');
//     }

//     refresh(); // 화면 업데이트
// }