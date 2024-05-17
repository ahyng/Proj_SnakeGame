#include "header/snake_game.h"

void moveSnake() {
    int nextX, nextY;

    while (true) {
        // 스네이크의 이동 로직
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

        // 벽에 닿았는지 확인
        if (nextX <= 0 || nextX >= SCREEN_WIDTH - 1 || nextY <= 0 || nextY >= SCREEN_HEIGHT - 1) {
            // 게임 오버
            game_over = true;
            mvprintw(SCREEN_HEIGHT / 2 - 1, SCREEN_WIDTH / 2 - 5, "Game Over"); // 게임 오버 메시지 출력
            mvprintw(SCREEN_HEIGHT / 2, SCREEN_WIDTH / 2 - 12, "Press any key to restart");
            refresh();
            getch();
            game_over = false; // 게임 종료 상태 해제
            // 스네이크 초기 설정
            initSnake();
            // 먹이 초기 설정
            initFood();
            // 독 초기 설정
            initPoison();
            // 초기에 스네이크가 오른쪽으로 움직이도록 설정
            direction = KEY_RIGHT;
            continue;
        }

        // 스네이크의 몸과 충돌 확인
        for (int i = 1; i < snakeLength; ++i) {
            if (nextX == snakeX[i] && nextY == snakeY[i]) {
                // 게임 오버
                game_over = true;
                mvprintw(SCREEN_HEIGHT / 2 - 1, SCREEN_WIDTH / 2 - 5, "Game Over"); // 게임 오버 메시지 출력
                mvprintw(SCREEN_HEIGHT / 2, SCREEN_WIDTH / 2 - 12, "Press any key to restart");
                refresh();
                getch();
                game_over = false; // 게임 종료 상태 해제
                // 스네이크 초기 설정
                initSnake();
                // 먹이 초기 설정
                initFood();
                // 독 초기 설정
                initPoison();
                // 초기에 스네이크가 오른쪽으로 움직이도록 설정
                direction = KEY_RIGHT;
                continue;
            }
        }

        if (snakeLength < 3){
            game_over = true;
            mvprintw(SCREEN_HEIGHT / 2 - 1, SCREEN_WIDTH / 2 - 5, "Game Over"); // 게임 오버 메시지 출력
            mvprintw(SCREEN_HEIGHT / 2, SCREEN_WIDTH / 2 - 12, "Press any key to restart");
            refresh();
            getch();
            game_over = false; // 게임 종료 상태 해제
            // 스네이크 초기 설정
            initSnake();
            // 먹이 초기 설정
            initFood();
            // 독 초기 설정
            initPoison();
            // 초기에 스네이크가 오른쪽으로 움직이도록 설정
            direction = KEY_RIGHT;
            continue;
        }

        // 게임 오버일 때 종료
        //if (game_over) {
            //break;
        //}

        // 새로운 위치에 스네이크 이동
        // 꼬리 제거
        mtx.lock(); // 뮤텍스 락
        mvaddch(snakeY[snakeLength - 1], snakeX[snakeLength - 1], ' ');
        for (int i = snakeLength - 1; i > 0; --i) {
            snakeX[i] = snakeX[i - 1];
            snakeY[i] = snakeY[i - 1];
        }
        snakeX[0] = nextX;
        snakeY[0] = nextY;

        // 먹이를 먹었는지 확인
        if (nextX == foodX && nextY == foodY) {
            snakeLength++; // 스네이크의 길이 증가
            initFood(); // 새로운 먹이 생성
        }

        // 독을 먹었는지 확인
        if (nextX == poisonX && nextY == poisonY) {
            snakeLength--; // 스네이크의 길이 감소
            initPoison(); // 새로운 독 생성
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