#include "header/snake_game.h"

void moveSnake() {
    int nextX, nextY;

    while (true) {
        updateGate(); // 게이트 업데이트 호출, 게이트 생성 및 타이머 관련 로직 처리
        checkGateCollision(); // 게이트와의 충돌 검사 및 처리 함수 호출

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
            mvprintw(SCREEN_HEIGHT / 2 - 1, SCREEN_WIDTH / 2 - 5, "Game Over"); // 게임 오버 메시지 출력
            mvprintw(SCREEN_HEIGHT / 2, SCREEN_WIDTH / 2 - 12, "Press any key to restart");
            refresh();
            getch();
            // 스네이크 초기 설정
            initSnake();
            // 아이템 초기 설정
            initFood();
            initPoison();
            // 초기에 스네이크가 오른쪽으로 움직이도록 설정
            direction = KEY_RIGHT;
            continue;
        }

        // 스네이크의 몸과 충돌 확인
        for (int i = 1; i < snakeLength; ++i) {
            if (nextX == snakeX[i] && nextY == snakeY[i]) {
                // 게임 오버
                mvprintw(SCREEN_HEIGHT / 2 - 1, SCREEN_WIDTH / 2 - 5, "Game Over"); // 게임 오버 메시지 출력
                mvprintw(SCREEN_HEIGHT / 2, SCREEN_WIDTH / 2 - 12, "Press any key to restart");
                refresh();
                getch();
                // 스네이크 초기 설정
                initSnake();
                // 아이템 초기 설정
                initFood();
                initPoison();
                // 초기에 스네이크가 오른쪽으로 움직이도록 설정
                direction = KEY_RIGHT;
                continue;
            }
        }

        // 장애물에 닿았는지 확인
        for (int i = 0; i < NUM_WALL; ++i) {
            if (nextX == wall[i][1] && nextY == wall[i][0]) {
                // 게임 오버
                mvprintw(SCREEN_HEIGHT / 2 - 1, SCREEN_WIDTH / 2 - 5, "Game Over"); // 게임 오버 메시지 출력
                mvprintw(SCREEN_HEIGHT / 2, SCREEN_WIDTH / 2 - 12, "Press any key to restart");
                refresh();
                getch();
                // 스네이크 초기 설정
                initSnake();
                // 아이템 초기 설정
                initFood();
                initPoison();
                // 초기에 스네이크가 오른쪽으로 움직이도록 설정
                direction = KEY_RIGHT;
                continue;
            }
        }

        if (nextX <= 0 || nextX >= SCREEN_WIDTH - 1 || nextY <= 0 || nextY >= SCREEN_HEIGHT - 1) {
            // 게임 오버
            mvprintw(SCREEN_HEIGHT / 2 - 1, SCREEN_WIDTH / 2 - 5, "Game Over"); // 게임 오버 메시지 출력
            mvprintw(SCREEN_HEIGHT / 2, SCREEN_WIDTH / 2 - 12, "Press any key to restart");
            refresh();
            getch();
            // 스네이크 초기 설정
            initSnake();
            // 아이템 초기 설정
            initFood();
            initPoison();
            // 초기에 스네이크가 오른쪽으로 움직이도록 설정
            direction = KEY_RIGHT;
            continue;
        }

        // 길이가 3보다 작을 때 종료
        if (snakeLength < 3){
            mvprintw(SCREEN_HEIGHT / 2 - 1, SCREEN_WIDTH / 2 - 5, "Game Over"); // 게임 오버 메시지 출력
            mvprintw(SCREEN_HEIGHT / 2, SCREEN_WIDTH / 2 - 12, "Press any key to restart");
            refresh();
            getch();
            // 스네이크 초기 설정
            initSnake();
            // 아이템 초기 설정
            initFood();
            initPoison();
            // 초기에 스네이크가 오른쪽으로 움직이도록 설정
            direction = KEY_RIGHT;
            continue;
        }

        mtx.lock(); // 뮤텍스 락
        mvaddch(snakeY[snakeLength - 1], snakeX[snakeLength - 1], ' ');
        for (int i = snakeLength - 1; i > 0; --i) {
            snakeX[i] = snakeX[i - 1];
            snakeY[i] = snakeY[i - 1];
        }
        snakeX[0] = nextX;
        snakeY[0] = nextY;

        // 먹이를 획득
        if (nextX == foodX && nextY == foodY) {
            snakeLength += (doubleActive ? 2 : 1); // 길이 증가 'double' 아이템 효과 적용
            initFood(); // 새로운 아이템 생성
        }
        // 독을 획득
        if (nextX == poisonX && nextY == poisonY) {
            snakeLength -= (doubleActive ? 2 : 1); // 길이 감소 'double' 아이템 효과 적용
            initPoison(); // 새로운 아이템 생성
        }
        // 더블 획득
        if (nextX == doubleX && nextY == doubleY) {
            doubleActive = true;
            doubleStartTime = std::chrono::steady_clock::now();
            initDouble();
        }

        // 'double' 아이템 지속 시간 확인
        if (doubleActive && std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - doubleStartTime).count() >= 10) {
            doubleActive = false;
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