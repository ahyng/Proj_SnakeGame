// move_snake.cpp
#include "header/snake_game.h"
#include <iostream>
using namespace std;

extern int foodEaten;
extern int mapState;

void moveSnake() {
    int nextX, nextY;
    bool teleporting = false;
    bool wallCollisionEnabled = true;
    int teleportSteps = 0;

    while (true) {
        nextX = snakeX[0];
        nextY = snakeY[0];
        switch (direction) {
            case KEY_UP:
                nextY--;
                break;
            case KEY_DOWN:
                nextY++;
                break;
            case KEY_LEFT:
                nextX--;
                break;
            case KEY_RIGHT:
                nextX++;
                break;
        }

        // 포털을 통한 이동
        if (nextX == portal1X && nextY == portal1Y) {
            nextX = portal2X;
            nextY = portal2Y;
            teleporting = true;
            wallCollisionEnabled = false;  // 벽 충돌 비활성화
            teleportSteps = snakeLength;

            // 포털 방향에 따라 반대 방향으로 설정
            if (portal2X == 0) direction = KEY_RIGHT;
            else if (portal2X == SCREEN_WIDTH - 1) direction = KEY_LEFT;
            else if (portal2Y == 0) direction = KEY_DOWN;
            else if (portal2Y == SCREEN_HEIGHT - 1) direction = KEY_UP;
            else if (portal2Y > SCREEN_HEIGHT / 2) direction = KEY_DOWN;
            else if (portal2X < SCREEN_WIDTH / 2) direction = KEY_LEFT;
            else if (portal2X > SCREEN_WIDTH / 2) direction = KEY_RIGHT;

        } else if (nextX == portal2X && nextY == portal2Y) {
            nextX = portal1X;
            nextY = portal1Y;
            teleporting = true;
            wallCollisionEnabled = false;  // 벽 충돌 비활성화
            teleportSteps = snakeLength;

            // 포털 방향에 따라 반대 방향으로 설정
            if (portal1X == 0) direction = KEY_RIGHT;
            else if (portal1X == SCREEN_WIDTH - 1) direction = KEY_LEFT;
            else if (portal1Y == 0) direction = KEY_DOWN;
            else if (portal1Y == SCREEN_HEIGHT - 1) direction = KEY_UP;
            else if (portal1Y > SCREEN_HEIGHT / 2) direction = KEY_DOWN;
            else if (portal1Y < SCREEN_HEIGHT / 2) direction = KEY_UP;
            else if (portal1X < SCREEN_WIDTH / 2) direction = KEY_LEFT;
            else if (portal1X > SCREEN_WIDTH / 2) direction = KEY_RIGHT;
        }

        // 벽 충돌 확인
        if (wallCollisionEnabled && mvinch(nextY, nextX) == '#') {
            resetGame();
            continue;
        }

        // 스네이크의 몸과 충돌 확인
        for (int i = 1; i < snakeLength; ++i) {
            if (nextX == snakeX[i] && nextY == snakeY[i]) {
                resetGame();
                continue;
            }
        }

        // 새로운 위치에 스네이크 이동
        mtx.lock(); // 뮤텍스 락
        mvaddch(snakeY[snakeLength - 1], snakeX[snakeLength - 1], ' ');
        for (int i = snakeLength - 1; i > 0; --i) {
            snakeX[i] = snakeX[i - 1];
            snakeY[i] = snakeY[i - 1];
        }
        snakeX[0] = nextX;
        snakeY[0] = nextY;

        // 포털을 완전히 빠져나온 후 벽 충돌 활성화
        if (teleporting) {
            teleportSteps--;
            if (teleportSteps <= 0) {
                teleporting = false;
                wallCollisionEnabled = true;  // 벽 충돌 활성화
                initPortals();
            }
        }

        // 먹이를 먹었는지 확인
        if (nextX == foodX && nextY == foodY) {
            snakeLength++;
            foodEaten++;  // 먹이를 먹은 횟수 증가
            initFood();
            score++;      // 점수 증가
            cout << "Food eaten: " << foodEaten << endl; // 디버깅 출력

            // 먹이를 3개 먹으면 맵 상태를 변경하고 다음 스테이지로 넘어가기
            if (checkConditionToChangeMap()) {
                mapState = 2; // 맵 상태 변경
                cout << "Map state changed to 2" << endl;
                waitForUserInput();
                drawMap(mapState); // 새로운 맵 상태로 다시 그리기
            }
        }

        // 독을 먹었는지 확인
        if (nextX == poisonX && nextY == poisonY) {
            snakeLength--;
            initPoison();
        }
        mtx.unlock(); // 뮤텍스 언락

        // 게임 화면 그리기
        drawScreen();

        // 조건 변수 통지
        cv.notify_one();

        // 일정 시간 동안 대기
        usleep(gameSpeed);
    }
}
