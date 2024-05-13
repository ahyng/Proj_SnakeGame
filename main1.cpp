#include <iostream>
#include <ncurses.h>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <unistd.h>


#define SCREEN_WIDTH 50
#define SCREEN_HEIGHT 20

// 스네이크의 최대 길이
#define MAX_LENGTH 100

int snakeX[MAX_LENGTH], snakeY[MAX_LENGTH]; // 스네이크의 좌표 배열
int snakeLength; // 스네이크의 길이
int direction; // 스네이크의 방향
int gameSpeed; // 게임 속도 (단위: 마이크로초)
std::mutex mtx; // mutex (상호 배제를 위해 사용)
std::condition_variable cv; // 조건 변수
bool game_over = false;

// 먹이의 위치
int foodX, foodY;

// 화면 초기 설정
void initScreen() {
    initscr(); // ncurses 초기화
    noecho(); // 키 입력 시 입력 내용을 화면에 보여주지 않음
    curs_set(0); // 커서를 보이지 않게 함
    keypad(stdscr, TRUE); // 특수 키 사용 가능하게 설정
    gameSpeed = 100000; // 초기 게임 속도 설정 (0.1초에 한 번)
}

// 스네이크 초기 설정
void initSnake() {
    snakeLength = 3; // 초기 스네이크의 길이는 3
    snakeX[0] = SCREEN_WIDTH / 2; // 화면의 중앙
    snakeY[0] = SCREEN_HEIGHT / 2; // 화면의 중앙
}

// 먹이 초기 설정
void initFood() {
    foodX = rand() % (SCREEN_WIDTH - 2) + 1;
    foodY = rand() % (SCREEN_HEIGHT - 2) + 1;
}

// 게임 화면 그리기
void drawScreen() {
    // 화면 클리어
    clear();

    // 네모 그리기
    for (int i = 0; i < SCREEN_WIDTH; ++i) {
        mvaddch(0, i, '#'); // 윗면
        mvaddch(SCREEN_HEIGHT - 1, i, '#'); // 아랫면
    }
    for (int i = 0; i < SCREEN_HEIGHT; ++i) {
        mvaddch(i, 0, '#'); // 왼쪽면
        mvaddch(i, SCREEN_WIDTH - 1, '#'); // 오른쪽면
    }

    // 먹이 그리기
    mvaddch(foodY, foodX, '@');

    // 스네이크 그리기
    for (int i = 0; i < snakeLength; ++i) {
        mvaddch(snakeY[i], snakeX[i], 'o');
    }

    refresh(); // 화면 업데이트
}

// 스네이크의 이동 로직
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
            mvprintw(SCREEN_HEIGHT / 2, SCREEN_WIDTH / 2 - 5, "Game Over"); // 게임 오버 메시지 출력
            mvprintw(SCREEN_HEIGHT / 2 + 1, SCREEN_WIDTH / 2 - 10, "Press any key to restart");
            refresh();
            getch();
            game_over = false; // 게임 종료 상태 해제
            break;
        }

        // 스네이크의 몸과 충돌 확인
        for (int i = 1; i < snakeLength; ++i) {
            if (nextX == snakeX[i] && nextY == snakeY[i]) {
                // 게임 오버
                game_over = true;
                mvprintw(SCREEN_HEIGHT / 2, SCREEN_WIDTH / 2 - 5, "Game Over"); // 게임 오버 메시지 출력
                mvprintw(SCREEN_HEIGHT / 2 + 1, SCREEN_WIDTH / 2 - 10, "Press any key to restart");
                refresh();
                getch();
                game_over = false; // 게임 종료 상태 해제
                break;
            }
        }

        // 게임 오버일 때 종료
        if (game_over) {
            break;
        }

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
        mtx.unlock(); // 뮤텍스 언락

        // 게임 화면 그리기
        drawScreen();

        // 조건 변수 통지
        cv.notify_one();

        // 일정 시간 동안 대기
        usleep(gameSpeed);
    }
}

// 사용자 입력 처리
void handleInput() {
    int ch;

    while (true) {
        // 키 입력 받아 스네이크의 방향 업데이트
        ch = getch();
        switch (ch) {
            case KEY_UP:
                if (direction != KEY_DOWN)
                    direction = KEY_UP;
                break;
            case KEY_DOWN:
                if (direction != KEY_UP)
                    direction = KEY_DOWN;
                break;
            case KEY_LEFT:
                if (direction != KEY_RIGHT)
                    direction = KEY_LEFT;
                break;
            case KEY_RIGHT:
                if (direction != KEY_LEFT)
                    direction = KEY_RIGHT;
                break;
        }
    }
}

// 게임 실행
void runGame() {
    // 스네이크의 이동 쓰레드 생성
    std::thread moveThread(moveSnake);

    // 사용자 입력 처리
    handleInput();

    // 쓰레드 종료
    moveThread.join();
}

// 게임 시작
void game_start() {
    // 스네이크 초기 설정
    initSnake();
    // 먹이 초기 설정
    initFood();
    // 초기에 스네이크가 오른쪽으로 움직이도록 설정
    direction = KEY_RIGHT;
    // 게임 화면 그리기
    drawScreen();
    // 게임 실행
    runGame();
}

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