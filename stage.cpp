#include "header/snake_game.h"

// 현재 점수를 추적하는 변수
int score = 0;
int foodEaten = 0;  // 먹이를 먹은 횟수 초기화

// 맵 상태를 추적하는 변수
int mapState = 1;

#include "header/snake_game.h"
#include <iostream>

bool checkConditionToChangeMap() {
    // 먹이를 3개 먹었을 때 맵 상태 변경
    if (foodEaten >= 3) {
        std::cout << "Changing map state to 2" << std::endl;
        return true;
    }
    return false;
}

void waitForUserInput() {
    clear();
    mvprintw(SCREEN_HEIGHT / 2, (SCREEN_WIDTH - 10) / 2, "Next Stage");
    mvprintw(SCREEN_HEIGHT / 2 + 1, (SCREEN_WIDTH - 25) / 2, "Press any key to continue...");
    refresh();
    getch();  // 키 입력 대기
}