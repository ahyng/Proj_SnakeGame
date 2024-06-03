#include "header/snake_game.h"

void game_start() {
    game_over = false; // 게임 오버 상태 초기화

    gameStartTime = std::chrono::steady_clock::now(); // 시작 시간 설정

    // 스네이크 초기 설정
    initSnake();

    // 먹이 초기 설정
    initFood();

    //독 초기 설정
    initPoison();

    // 더블 초기설정
    initDouble();

    // 초기에 스네이크가 오른쪽으로 움직이도록 설정
    direction = KEY_RIGHT;

    // 게이트 업데이트 쓰레드 생성
    std::thread portalThread(updatePortals);

    // 게이트 초기 설정
    initPortals();
    // 게임 화면 그리기
    drawScreen();

    // 게임 실행
    runGame();

    // ncurses 종료
    endwin();

    // 게이트 쓰레드 종료
    portalThread.join();
}