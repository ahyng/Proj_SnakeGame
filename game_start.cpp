#include "header/snake_game.h"

void game_start() {
    // 스네이크 초기 설정
    initSnake();
    // 아이템 초기 설정
    initFood();
    initPoison();
    // 초기에 스네이크가 오른쪽으로 움직이도록 설정
    direction = KEY_RIGHT;
    // 게임 화면 그리기
    drawScreen();
    // 게임 실행
    runGame();
}