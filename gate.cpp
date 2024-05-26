#include "header/snake_game.h"

// Gate 관련 변수 정의
bool gateCondition = false; // 게이트 존재 여부
std::pair<int, int> gate1(0, 0); // 첫 번째 게이트 위치
std::pair<int, int> gate2(0, 0); // 두 번째 게이트 위치
std::mutex mtxG;

// 게이트 생성 함수
void generateGate() {
    std::lock_guard<std::mutex> lk(mtxG);

    bool validPosition = false;
    while (!validPosition) {
        validPosition = true;
    
        // 화면 가장자리에 게이트 생성
        int gate1Side = std::rand() % 4; // 0: 상단, 1: 하단, 2: 좌측, 3: 우측
        int gate2Side;
        do {
            gate2Side = std::rand() % 4;
        } while (gate1Side == gate2Side); // 같은 면에 생성되지 않도록 함
        
        // 첫 번째 게이트 위치 설정
        switch(gate1Side) {
            case 0: // 상단
                gate1 = {1, std::rand() % (SCREEN_WIDTH - 2) + 1};
                break;
            case 1: // 하단
                gate1 = {SCREEN_HEIGHT - 2, std::rand() % (SCREEN_WIDTH - 2) + 1};
                break;
            case 2: // 좌측
                gate1 = {std::rand() % (SCREEN_HEIGHT - 2) + 1, 1};
                break;
            case 3: // 우측
                gate1 = {std::rand() % (SCREEN_HEIGHT - 2) + 1, SCREEN_WIDTH - 2};
                break;
        }
        
        // 두 번째 게이트 위치 설정
        switch(gate2Side) {
            case 0: // 상단
                gate2 = {1, std::rand() % (SCREEN_WIDTH - 2) + 1};
                break;
            case 1: // 하단
                gate2 = {SCREEN_HEIGHT - 2, std::rand() % (SCREEN_WIDTH - 2) + 1};
                break;
            case 2: // 좌측
                gate2 = {std::rand() % (SCREEN_HEIGHT - 2) + 1, 1};
                break;
            case 3: // 우측
                gate2 = {std::rand() % (SCREEN_HEIGHT - 2) + 1, SCREEN_WIDTH - 2};
                break;
        }

        // 생성된 게이트 위치가 먹이나 독과 겹치는지 검사
        if ((gate1.first == foodX && gate1.second == foodY) ||
            (gate1.first == poisonX && gate1.second == poisonY) ||
            (gate2.first == foodX && gate2.second == foodY) ||
            (gate2.first == poisonX && gate2.second == poisonY)) {
            validPosition = false; // 충돌 시 재시도
        }
    }
    gateCondition = true;
}

// 게이트 업데이트 함수
void updateGate() {
    // 게이트 생성 조건 확인 및 생성
    if (!gateCondition) {
        // 예시 1: 게임 시작 후 5초마다 게이트 생성
        static auto lastGateTime = std::chrono::steady_clock::now();
        auto now = std::chrono::steady_clock::now();
        if (std::chrono::duration_cast<std::chrono::seconds>(now - lastGateTime).count() > 5) {
            generateGate();
            lastGateTime = now;
        }
        
        // 예시 2: 몸의 길이가 10을 초과할 경우 게이트 생성
        if (snakeLength > 10 && !gateCondition) {
            generateGate();
        }
    }
}

// 게이트와의 충돌 검사 및 처리 함수
void checkGateCollision() {
    if (gateCondition) {
        std::lock_guard<std::mutex> lk(mtxG);
        // 뱀의 머리가 게이트에 도달했는지 확인
        if ((snakeX[0] == gate1.first && snakeY[0] == gate1.second) ||
            (snakeX[0] == gate2.first && snakeY[0] == gate2.second)) {
            // 게이트를 통과하는 로직 구현
            // 예시: 게이트1에 들어가면 게이트2로 나오도록 설정
            if (snakeX[0] == gate1.first && snakeY[0] == gate1.second) {
                snakeX[0] = gate2.first;
                snakeY[0] = gate2.second;
            } else {
                snakeX[0] = gate1.first;
                snakeY[0] = gate1.second;
            }
            
            // 게이트 통과 후 방향 조정 로직 구현 (간단한 예시)
            if (snakeX[0] == gate2.first && snakeY[0] == gate2.second) {
                // 게이트2로 나온 경우
                if (gate2.first == 1) { // 상단 벽에 붙어있는 경우
                    direction = KEY_DOWN; // 아래로 이동
                } else if (gate2.first == SCREEN_HEIGHT - 2) { // 하단 벽
                    direction = KEY_UP; // 위로 이동
                } else if (gate2.second == 1) { // 좌측 벽
                    direction = KEY_RIGHT; // 오른쪽으로 이동
                } else if (gate2.second == SCREEN_WIDTH - 2) { // 우측 벽
                    direction = KEY_LEFT; // 왼쪽으로 이동
                }
            }
            
            // 게이트 제거
            gateCondition = false;
            gate1 = {-1, -1};
            gate2 = {-1, -1};
        }
    }
}
