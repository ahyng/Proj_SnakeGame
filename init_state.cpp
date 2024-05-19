#include "header/snake_game.h"

// 헤더파일에 선언한 변수들 정의
int snakeX[MAX_LENGTH];
int snakeY[MAX_LENGTH];
int snakeLength;
int direction;
int gameSpeed;
std::mutex mtx;
std::condition_variable cv;
bool game_over;
int foodX, foodY;
int poisonX, poisonY;
std::chrono::steady_clock::time_point lastFoodTime;
std::chrono::steady_clock::time_point lastPoisonTime;

void initScreen() {
    initscr();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    gameSpeed = 100000;
}

void initSnake() {
    // 스네이크 초기 설정
    snakeLength = 3;
    snakeX[0] = SCREEN_WIDTH / 2;
    snakeY[0] = SCREEN_HEIGHT / 2;
}

void initItem() {
    // 아이템 초기 설정 로직
    foodX = rand() % (SCREEN_WIDTH - 2) + 1;
    foodY = rand() % (SCREEN_HEIGHT - 2) + 1;
    poisonX = rand() % (SCREEN_WIDTH - 2) + 1;
    poisonY = rand() % (SCREEN_HEIGHT - 2) + 1;
    lastFoodTime = std::chrono::steady_clock::now();
    lastPoisonTime = std::chrono::steady_clock::now();
    // 뮤텍스 잠금 없이 아이템 초기화
}

void updateItem() {
    // 아이템 위치 5초마다 업데이트
    while (!game_over) {
        std::this_thread::sleep_for(std::chrono::seconds(1));

        std::unique_lock<std::mutex> lk(mtx);
        auto now = std::chrono::steady_clock::now();

        if (std::chrono::duration_cast<std::chrono::seconds>(now - lastFoodTime).count() >= 5 ||
            std::chrono::duration_cast<std::chrono::seconds>(now - lastPoisonTime).count() >= 5) {
            initItem();
        }
        lk.unlock(); // 필요에 따라 수동으로 언락 가능

        cv.notify_all();
    }
}
