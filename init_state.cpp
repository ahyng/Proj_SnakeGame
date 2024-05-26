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
int doubleX, doubleY; // 'double' 아이템의 위치
std::chrono::steady_clock::time_point lastFoodTime;
std::chrono::steady_clock::time_point lastPoisonTime;
std::chrono::steady_clock::time_point lastDoubleTime; // 'double' 아이템의 마지막 갱신 시간
bool doubleActive = false; // 'double' 아이템 활성화 여부
std::chrono::steady_clock::time_point doubleStartTime; // 'double' 아이템 활성화 시작 시간

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

bool itemPosition(int x, int y) {
    // 벽과 겹치는지 확인
    for (int i = 0; i < NUM_WALL; ++i) {
        if (wall[i][0] == y && wall[i][1] == x) {
            return false;
        }
    }
    return true;
}

void initFood() {
    // 아이템 초기 설정 로직
    do {
        foodX = rand() % (SCREEN_WIDTH - 2) + 1;
        foodY = rand() % (SCREEN_HEIGHT - 2) + 1;
    } while (!itemPosition(foodX, foodY));
    lastFoodTime = std::chrono::steady_clock::now();
}

void initPoison() {
    // 아이템 초기 설정 로직
    do {
        poisonX = rand() % (SCREEN_WIDTH - 2) + 1;
        poisonY = rand() % (SCREEN_HEIGHT - 2) + 1;
    } while (!itemPosition(poisonX, poisonY));
    lastPoisonTime = std::chrono::steady_clock::now();
}

void initDouble() {
    // 'double' 아이템 초기 설정 로직
    do {
        doubleX = rand() % (SCREEN_WIDTH - 2) + 1;
        doubleY = rand() % (SCREEN_HEIGHT - 2) + 1;
    } while (!itemPosition(doubleX, doubleY));
    lastDoubleTime = std::chrono::steady_clock::now();
}

void updateItem() {
    // 아이템 위치 5초마다 업데이트
    while (!game_over) {
        std::this_thread::sleep_for(std::chrono::seconds(1));

        std::unique_lock<std::mutex> lk(mtx);
        auto now = std::chrono::steady_clock::now();

        if (std::chrono::duration_cast<std::chrono::seconds>(now - lastFoodTime).count() >= 5) {
            initFood();
        }
        if (std::chrono::duration_cast<std::chrono::seconds>(now - lastPoisonTime).count() >= 5) {
            initPoison();
        }
        if (std::chrono::duration_cast<std::chrono::seconds>(now - lastDoubleTime).count() >= 5) {
            initDouble();
        }
        lk.unlock(); // 필요에 따라 수동으로 언락 가능

        cv.notify_all();
    }
}
