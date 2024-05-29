#include "header/snake_game.h"
#include <iostream>
using namespace std;

void game_start() {
    // 스네이크 초기 설정
    initSnake();
    // 먹이 초기 설정
    initFood();
    //독 초기 설정
    initPoison();
    // 초기에 스네이크가 오른쪽으로 움직이도록 설정
    direction = KEY_RIGHT;
    std::thread portalThread(updatdPortals);
    //게이트 그리기
    initPortals();
    // 조건을 확인하여 맵 상태 변경
        if (checkConditionToChangeMap()) {
            mapState = 2; // 맵 상태 변경
            cout << "Map state changed to 2" << endl; // 디버깅 출력
        }
    // 게임 화면 그리기
    drawScreen();
    // 게임 실행
    runGame();
}