#include "header/snake_game.h"

void runGame() {
    // 스네이크의 이동 쓰레드 생성
    std::thread moveThread(moveSnake);

    // 사용자 입력 처리
    handleInput();

    // 쓰레드 종료
    moveThread.join();
}