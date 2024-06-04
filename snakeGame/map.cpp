#include "header/snake_game.h"

int wall[NUM_WALL][2];

void drawMap(int mapState){
    clear(); // 화면을 지우고 새로 그리기 위해 추가
    int index = 0;
    // 첫 번째 맵 상태
    if (mapState == 1) {
        for (int i = 0; i < SCREEN_WIDTH; ++i) {
            mvaddch(0, i, '#'); // 윗면
            mvaddch(SCREEN_HEIGHT - 1, i, '#'); // 아랫면
        }
        for (int i = 0; i < SCREEN_HEIGHT; ++i) {
            mvaddch(i, 0, '#'); // 왼쪽면
            mvaddch(i, SCREEN_WIDTH - 1, '#'); // 오른쪽면
        }
    }
    // 두 번째 맵 상태
    else if (mapState == 2) {
        for (int i = 0; i < SCREEN_WIDTH; ++i) {
            mvaddch(0, i, '#'); // 윗면
            mvaddch(SCREEN_HEIGHT - 1, i, '#'); // 아랫면
        }
        for (int i = 0; i < SCREEN_HEIGHT; ++i) {
            mvaddch(i, 0, '#'); // 왼쪽면
            mvaddch(i, SCREEN_WIDTH - 1, '#'); // 오른쪽면
        }
        for (int i = 11; i < 25; ++i) {
            mvaddch(5, i, '#'); // 안쪽 윗면
        }
        for (int i = 26; i < 41; ++i) {
            mvaddch(SCREEN_HEIGHT - 6, i, '#'); // 안쪽 아랫면
        }
        for (int i = 5; i < 10; ++i) {
            mvaddch(i, 10, '#'); // 안쪽 왼쪽면
        }
        for (int i = 9; i < 14; ++i) {
            mvaddch(i, SCREEN_WIDTH - 10, '#'); // 안쪽 오른쪽면
        }
    }
    // 세 번째 맵 상태
    else if (mapState == 3) {
        for (int i = 0; i < SCREEN_WIDTH; ++i) {
            mvaddch(0, i, '#'); // 윗면
            mvaddch(SCREEN_HEIGHT - 1, i, '#'); // 아랫면
        }
        for (int i = 0; i < SCREEN_HEIGHT; ++i) {
            mvaddch(i, 0, '#'); // 왼쪽면
            mvaddch(i, SCREEN_WIDTH - 1, '#'); // 오른쪽면
        }
        for (int i = 7; i < SCREEN_HEIGHT-6; ++i) {
            mvaddch(i, 12, '#'); // 왼쪽면
            mvaddch(i, SCREEN_WIDTH - 12, '#'); // 오른쪽면
        }
        for (int i = 12; i < SCREEN_WIDTH-11; ++i) {
            mvaddch(SCREEN_HEIGHT - 6, i, '#'); // 아랫면
        }
    }
    // 네 번째 맵 상태
    else if (mapState == 4){
        // 상단 테두리 그리기
        for (int i = 0; i < SCREEN_WIDTH; ++i) {
            mvaddch(0, i, '#');
        }

        // 하단 테두리 그리기
        for (int i = 0; i < SCREEN_WIDTH; ++i) {
            mvaddch(SCREEN_HEIGHT - 1, i, '#');
        }

        // 좌측 테두리 그리기
        for (int i = 0; i < SCREEN_HEIGHT; ++i) {
            mvaddch(i, 0, '#');
        }

        // 우측 테두리 그리기
        for (int i = 0; i < SCREEN_HEIGHT; ++i) {
            mvaddch(i, SCREEN_WIDTH - 1, '#');
        }

        // 중앙을 기준으로 십자가 형태의 맵 그리기
        int centerX = SCREEN_WIDTH / 2;
        int centerY = SCREEN_HEIGHT / 2;

        for (int i = -5; i <= 5; ++i) {
            mvaddch(centerY + i, centerX - abs(i), '#');
            mvaddch(centerY + i, centerX + abs(i), '#');
        }
    }
    else if (mapState == 5){
        for (int i = 0; i < SCREEN_WIDTH; ++i) {
        mvaddch(0, i, '#'); // 윗면
        mvaddch(SCREEN_HEIGHT - 1, i, '#'); // 아랫면
    }
    for (int i = 0; i < SCREEN_HEIGHT; ++i) {
        mvaddch(i, 0, '#'); // 왼쪽면
        mvaddch(i, SCREEN_WIDTH - 1, '#'); // 오른쪽면
    }
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
    }
    refresh(); // 화면을 업데이트
}