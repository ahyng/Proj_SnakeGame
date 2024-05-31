#include <iostream>
#include <ncurses.h>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <unistd.h> // for usleep

#include "header/snake_game.h"

int main() {
    // 시드 설정
    srand(time(NULL));

    // 화면 초기 설정
    initScreen();

    // 아이템 위치 업데이트 스레드 시작
    std::thread itemThread(updateItem); 

    // 게임 시작
    game_start();

    // 게임이 끝난 후 스레드 정리
    itemThread.join();

    // ncurses 종료
    endwin();

    return 0;
}