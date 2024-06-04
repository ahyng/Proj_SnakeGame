#include "header/snake_game.h"

void handleInput() {
    int ch;

    while (true) {
        // 키 입력 받아 스네이크의 방향 업데이트
        ch = getch();
        switch (ch) {
            // tail 방향으로 이동시 gameover
            case KEY_UP:
                if (direction == KEY_DOWN) {game_over = true;}
                    else {direction = KEY_UP;}
                break;
            case KEY_DOWN:
                if (direction == KEY_UP) {game_over = true;}
                    else {direction = KEY_DOWN;}
                break;
            case KEY_LEFT:
                if (direction == KEY_RIGHT) {game_over = true;}
                    else {direction = KEY_LEFT;}
                break;
            case KEY_RIGHT:
                if (direction == KEY_LEFT) {game_over = true;}
                    else {direction = KEY_RIGHT;}
                break;
        }
    }
}