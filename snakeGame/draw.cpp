#include "header/snake_game.h"

void drawScreen() {
    // 화면 클리어
    clear();

    drawMap(mapState);

    // 먹이 그리기
    mvaddch(foodY, foodX, '@');

    //독 그리기
    mvaddch(poisonY, poisonX, '%');

    // 더블 그리기
    mvaddch(doubleY, doubleX, '&');

    // 스네이크 그리기
    for (int i = 0; i < snakeLength; ++i) {
        mvaddch(snakeY[i], snakeX[i], 'O');
    }

    // 게이트 그리기
    mvaddch(portal1Y, portal1X, ' ');
    mvaddch(portal2Y, portal2X, ' ');

    // Score Board 표시
    auto now = std::chrono::steady_clock::now();
    int gameTimeSeconds = std::chrono::duration_cast<std::chrono::seconds>(now - gameStartTime).count();
    float B = static_cast<float>(snakeLength) / MAX_LENGTH;
    mvprintw(1, SCREEN_WIDTH + 5, "Score Board");
    mvprintw(3, SCREEN_WIDTH + 5, "B: %.2f", B);
    mvprintw(4, SCREEN_WIDTH + 5, "+: %d", growthItemCount);
    mvprintw(5, SCREEN_WIDTH + 5, "-: %d", poisonItemCount);
    mvprintw(6, SCREEN_WIDTH + 5, "G: %d", gateCount); // 게이트 사용 횟수, 필요시 수정
    mvprintw(8, SCREEN_WIDTH + 5, "Time: %d seconds", gameTimeSeconds);

    if (mapState == 1){
        // Mission 표시
        mvprintw(10, SCREEN_WIDTH + 5, "Mission1");
        mvprintw(11, SCREEN_WIDTH + 5, "B: 5 (%s)", (snakeLength >= 5 ? "v" : " "));
        mvprintw(12, SCREEN_WIDTH + 5, "+: 2 (%s)", (growthItemCount >= 2 ? "v" : " "));
        mvprintw(13, SCREEN_WIDTH + 5, "-: - (%s)", (poisonItemCount >= 0 ? "-" : " "));
        mvprintw(14, SCREEN_WIDTH + 5, "G: - (%s)", (gateCount >= 0 ? "-" : " ")); // 게이트 사용 횟수, 필요시 수정
        refresh(); // 화면 업데이트
    }
    else if (mapState == 2){
        // Mission 표시
        mvprintw(10, SCREEN_WIDTH + 5, "Mission2");
        mvprintw(11, SCREEN_WIDTH + 5, "B: 10 (%s)", (snakeLength >= 10 ? "v" : " "));
        mvprintw(12, SCREEN_WIDTH + 5, "+: 5 (%s)", (growthItemCount >= 5 ? "v" : " "));
        mvprintw(13, SCREEN_WIDTH + 5, "-: 2 (%s)", (poisonItemCount >= 2 ? "v" : " "));
        mvprintw(14, SCREEN_WIDTH + 5, "G: 1 (%s)", (gateCount >= 1 ? "v" : " ")); // 게이트 사용 횟수, 필요시 수정
        refresh(); // 화면 업데이트
    }
    else if (mapState == 3){
        // Mission 표시
        mvprintw(10, SCREEN_WIDTH + 5, "Mission3");
        mvprintw(11, SCREEN_WIDTH + 5, "B: 10 (%s)", (snakeLength >= 10 ? "v" : " "));
        mvprintw(12, SCREEN_WIDTH + 5, "+: 5 (%s)", (growthItemCount >= 5 ? "v" : " "));
        mvprintw(13, SCREEN_WIDTH + 5, "-: 2 (%s)", (poisonItemCount >= 2 ? "v" : " "));
        mvprintw(14, SCREEN_WIDTH + 5, "G: 1 (%s)", (gateCount >= 1 ? "v" : " ")); // 게이트 사용 횟수, 필요시 수정
        refresh(); // 화면 업데이트
    }
    else if (mapState == 4){
        // Mission 표시
        mvprintw(10, SCREEN_WIDTH + 5, "Mission4");
        mvprintw(11, SCREEN_WIDTH + 5, "B: 10 (%s)", (snakeLength >= 10 ? "v" : " "));
        mvprintw(12, SCREEN_WIDTH + 5, "+: 5 (%s)", (growthItemCount >= 5 ? "v" : " "));
        mvprintw(13, SCREEN_WIDTH + 5, "-: 2 (%s)", (poisonItemCount >= 2 ? "v" : " "));
        mvprintw(14, SCREEN_WIDTH + 5, "G: 1 (%s)", (gateCount >= 1 ? "v" : " ")); // 게이트 사용 횟수, 필요시 수정
        refresh(); // 화면 업데이트
    }
    else if (mapState == 5){
        // Mission 표시
        mvprintw(10, SCREEN_WIDTH + 5, "Mission5");
        mvprintw(11, SCREEN_WIDTH + 5, "B: 10 (%s)", (snakeLength >= 10 ? "v" : " "));
        mvprintw(12, SCREEN_WIDTH + 5, "+: 5 (%s)", (growthItemCount >= 5 ? "v" : " "));
        mvprintw(13, SCREEN_WIDTH + 5, "-: 2 (%s)", (poisonItemCount >= 2 ? "v" : " "));
        mvprintw(14, SCREEN_WIDTH + 5, "G: 1 (%s)", (gateCount >= 1 ? "v" : " ")); // 게이트 사용 횟수, 필요시 수정
        refresh(); // 화면 업데이트
    }
}