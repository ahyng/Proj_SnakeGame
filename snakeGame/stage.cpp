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
    if (mapState == 1 && snakeLength >= 5 && gateCount >= 1 && poisonItemCount >= 1) {
        return true;
    }
    // 먹이를 5개 먹었을 때 맵 상태 변경
    else if (mapState == 2 && gateCount >= 3) {
        return true;
    }
    // 먹이를 7개 먹었을 때 맵 상태 변경
    else if (mapState == 3 && growthItemCount >= 7) {
        return true;
    }
    // 먹이를 10개 먹었을 때 맵 상태 변경
    else if (mapState == 4 && growthItemCount >= 10) {
        return true;
    }
    else if (mapState == 5 && growthItemCount >= 10) {
        return true;
    }
    return false;
}

void waitForUserInput() {
    clear();
    if (mapState == 5){
        mvprintw(SCREEN_HEIGHT / 2, (SCREEN_WIDTH - 10) / 2, "Game Clear!");
    } else {
        mvprintw(SCREEN_HEIGHT / 2, (SCREEN_WIDTH - 10) / 2, "Next Stage");
        mvprintw(SCREEN_HEIGHT / 2 + 1, (SCREEN_WIDTH - 25) / 2, "Press any key to continue...");
        refresh();
        getch();  // 키 입력 대기
    }
    
}