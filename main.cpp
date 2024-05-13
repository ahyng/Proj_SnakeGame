#include <iostream>
#include <ncurses.h>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <unistd.h> // for usleep

#include "header/snake_game.h"
#include "draw.cpp"
#include "game_start.cpp"
#include "init_state.cpp"
#include "run.cpp"
#include "move_snake.cpp"
#include "handle.cpp"


int main() {
    // 시드 설정
    srand(time(NULL));

    // 화면 초기 설정
    initScreen();

    // 게임 시작
    game_start();
    
    // ncurses 종료
    endwin();

    return 0;
}
