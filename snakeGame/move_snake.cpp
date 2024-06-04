#include "header/snake_game.h"
#include <algorithm>

using namespace std;
int key[4] = {KEY_UP, KEY_RIGHT, KEY_DOWN, KEY_LEFT};

void moveSnake() {
    int nextX, nextY;
    bool teleporting = false;
    bool wallCollisionEnabled = true;
    int teleportSteps = 0;

    while (true) {
        nextX = snakeX[0];
        nextY = snakeY[0];
        // tail 방향으로 이동시 gameover
        if (game_over == true){
            mvprintw(SCREEN_HEIGHT / 2 - 1, SCREEN_WIDTH / 2 - 5, "Game Over");
                mvprintw(SCREEN_HEIGHT / 2, SCREEN_WIDTH / 2 - 12, "Press any key to restart");
                refresh();
                getch();
                game_over = false;
                srand(time(0)); // Re-seed the random number generator for each restart
                initSnake();
                initFood();
                initPoison();
                initDouble();
                initPortals();
                direction = KEY_RIGHT;
                gateCount = 0;
                growthItemCount = 0;  // 먹은 먹이 수 초기화
                poisonItemCount = 0;
                mapState = 1; // 맵 상태를 1로 설정
                continue;
        }
        
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
            if (portal2X == 0) direction = KEY_RIGHT; // 나오는 포털이 왼쪽에 있다면 오른쪽을 바라보기
            else if (portal2X == SCREEN_WIDTH - 1) direction = KEY_LEFT; // 나오는 포털이 오른쪽에 있다면 왼쪽을 바라보기
            else if (portal2Y == 0) direction = KEY_DOWN; // 나오는 포털이 위에 있다면 아래를 바라보기
            else if (portal2Y == SCREEN_HEIGHT - 1) direction = KEY_UP; // 나오는 포털이 아래에 있다면 위를 바라보기

            //map2
            else if (mapState == 2){           
                if (portal2Y == 5 || portal2Y == SCREEN_HEIGHT - 6){
                    auto i = find(begin(key), end(key), direction);
                    int index = distance(begin(key), i);
                    if (direction != KEY_UP && direction != KEY_DOWN) {
                        direction = key[(index+1) % 4];    
                    }
                }
                
                else if (portal2X == SCREEN_WIDTH - 10 || portal2X == 10){
                    auto i = find(begin(key), end(key), direction);
                    int index = distance(begin(key), i);
                    if (direction != KEY_RIGHT && direction != KEY_LEFT) {
                        direction = key[(index+1) % 4];    
                    }
                }
                
            } 

            //map3
            else if (mapState == 3){
                if (portal2Y == SCREEN_HEIGHT - 6){
                    auto i = find(begin(key), end(key), direction);
                    int index = distance(begin(key), i);
                    if (direction != KEY_UP && direction != KEY_DOWN) {
                        direction = key[(index+1) % 4];    
                    }
                }

                else if (portal2X == SCREEN_WIDTH - 12 || portal2X == 12){
                    auto i = find(begin(key), end(key), direction);
                    int index = distance(begin(key), i);
                    if (direction != KEY_RIGHT && direction != KEY_LEFT) {
                        direction = key[(index+1) % 4];    
                    }
                }

            }

            //map4
            else if (mapState == 4){
                if (portal2X < SCREEN_WIDTH / 2) direction = KEY_LEFT;
                else if (portal2X > SCREEN_WIDTH / 2) direction = KEY_RIGHT;
            }

            //map5
            else if (mapState == 5){
                if (portal2Y == 6 || portal2Y == SCREEN_HEIGHT-7){
                    auto i = find(begin(key), end(key), direction);
                    int index = distance(begin(key), i);
                    if (direction != KEY_UP && direction != KEY_DOWN) {
                        direction = key[(index+1) % 4];    
                    }
                }

                else if (portal2X == 15){
                    auto i = find(begin(key), end(key), direction);
                    int index = distance(begin(key), i);
                    if (direction != KEY_RIGHT && direction != KEY_LEFT) {
                        direction = key[(index+1) % 4];    
                    }
                }

            }


        } else if (nextX == portal2X && nextY == portal2Y) {
            nextX = portal1X;
            nextY = portal1Y;
            teleporting = true;
            wallCollisionEnabled = false;  // 벽 충돌 비활성화
            teleportSteps = snakeLength;

            // 포털 방향에 따라 반대 방향으로 설정
            if (portal1X == 0) direction = KEY_RIGHT; // 나오는 포털이 왼쪽에 있다면 오른쪽을 바라보기
            else if (portal1X == SCREEN_WIDTH - 1) direction = KEY_LEFT; // 나오는 포털이 오른쪽에 있다면 왼쪽을 바라보기
            else if (portal1Y == 0) direction = KEY_DOWN; // 나오는 포털이 위에 있다면 아래를 바라보기
            else if (portal1Y == SCREEN_HEIGHT - 1) direction = KEY_UP; // 나오는 포털이 아래에 있다면 위를 바라보기
            
            //다른맵

            //map2
            else if (mapState == 2){
                if (portal1Y == 5 || portal1Y == SCREEN_HEIGHT - 6){
                    auto i = find(begin(key), end(key), direction);
                    int index = distance(begin(key), i);
                    if (direction != KEY_UP && direction != KEY_DOWN) {
                        direction = key[(index+1) % 4];
                    }
                }
                
                else if (portal1X == SCREEN_WIDTH - 10 || portal1X == 10){
                    auto i = find(begin(key), end(key), direction);
                    int index = distance(begin(key), i);
                    if (direction != KEY_RIGHT && direction != KEY_LEFT) {
                        direction = key[(index+1) % 4];    
                    }
                }
                
            } 

            //map3
            else if (mapState == 3){
                if (portal1Y == SCREEN_HEIGHT - 6){
                    auto i = find(begin(key), end(key), direction);
                    int index = distance(begin(key), i);
                    if (direction != KEY_UP && direction != KEY_DOWN) {
                        direction = key[(index+1) % 4];    
                    }
                }

                else if (portal1X == SCREEN_WIDTH - 12 || portal1X == 12){
                    auto i = find(begin(key), end(key), direction);
                    int index = distance(begin(key), i);
                    if (direction != KEY_RIGHT && direction != KEY_LEFT) {
                        direction = key[(index+1) % 4];    
                    }
                }
            }

            //map4
            else if (mapState == 4){
                if (portal1X < SCREEN_WIDTH / 2) direction = KEY_LEFT;
                else if (portal1X > SCREEN_WIDTH / 2) direction = KEY_RIGHT;
            }

            //map5
            else if (mapState == 5){
                if (portal1Y == 6 || portal1Y == SCREEN_HEIGHT-7){
                    auto i = find(begin(key), end(key), direction);
                    int index = distance(begin(key), i);
                    if (direction != KEY_UP && direction != KEY_DOWN) {
                        direction = key[(index+1) % 4];    
                    }
                }

                else if (portal1X == 15){
                    auto i = find(begin(key), end(key), direction);
                    int index = distance(begin(key), i);
                    if (direction != KEY_RIGHT && direction != KEY_LEFT) {
                        direction = key[(index+1) % 4];    
                    }
                }
            }
        }

        // if (wallCollisionEnabled && (
        //     nextX <= 0 || nextX >= SCREEN_WIDTH - 1 || 
        //     nextY <= 0 || nextY >= SCREEN_HEIGHT - 1 ||
        //     ((nextX >= INNER_LEFT) && (nextX <= INNER_RIGHT) && (nextY == INNER_TOP) && (nextX != (INNER_LEFT + INNER_RIGHT) / 2)) ||
        //     ((nextX >= INNER_LEFT) && (nextX <= INNER_RIGHT) && (nextY == INNER_BOTTOM) && (nextX != (INNER_LEFT + INNER_RIGHT) / 2)) ||
        //     ((nextY >= INNER_TOP) && (nextY <= INNER_BOTTOM) && (nextX == INNER_LEFT) && (nextY != (INNER_TOP + INNER_BOTTOM) / 2)) ||
        //     ((nextY >= INNER_TOP) && (nextY <= INNER_BOTTOM) && (nextX == INNER_RIGHT) && (nextY != (INNER_TOP + INNER_BOTTOM) / 2)))) {
        //     game_over = true;
        //     mvprintw(SCREEN_HEIGHT / 2 - 1, SCREEN_WIDTH / 2 - 5, "Game Over");
        //     mvprintw(SCREEN_HEIGHT / 2, SCREEN_WIDTH / 2 - 12, "Press any key to restart");
        //     refresh();
        //     getch();
        //     game_over = false;
        //     srand(time(0)); // Re-seed the random number generator for each restart
        //     initSnake();
        //     initFood();
        //     initPoison();
        //     initDouble();
        //     initPortals();
        //     direction = KEY_RIGHT;
        //     continue;
        // }

        // 다음 이동할 곳에 #이 있을 경우에 게임오버 되도록 구현
         if (wallCollisionEnabled && mvinch(nextY, nextX) == '#') {
                game_over = true;
                mvprintw(SCREEN_HEIGHT / 2 - 1, SCREEN_WIDTH / 2 - 5, "Game Over");
                mvprintw(SCREEN_HEIGHT / 2, SCREEN_WIDTH / 2 - 12, "Press any key to restart");
                refresh();
                getch();
                game_over = false;
                srand(time(0)); // Re-seed the random number generator for each restart
                initSnake();
                initFood();
                initPoison();
                initDouble();
                initPortals();
                direction = KEY_RIGHT;
                gateCount = 0;
                growthItemCount = 0;  // 먹은 먹이 수 초기화
                poisonItemCount = 0;
                mapState = 1; // 맵 상태를 1로 설정
                // 포탈 업데이트를 시작합니다.
                std::thread portalThread(updatePortals);
                portalThread.detach(); // 스레드를 백그라운드에서 실행합니다.
                continue;
            }

        // 스네이크의 몸과 충돌 확인
        for (int i = 1; i < snakeLength; ++i) {
            if (nextX == snakeX[i] && nextY == snakeY[i]) {
                game_over = true;
                mvprintw(SCREEN_HEIGHT / 2 - 1, SCREEN_WIDTH / 2 - 5, "Game Over");
                mvprintw(SCREEN_HEIGHT / 2, SCREEN_WIDTH / 2 - 12, "Press any key to restart");
                refresh();
                getch();
                game_over = false;
                srand(time(0)); // Re-seed the random number generator for each restart
                initSnake();
                initFood();
                initPoison();
                initDouble();
                initPortals();
                direction = KEY_RIGHT;
                gateCount = 0;
                growthItemCount = 0;  // 먹은 먹이 수 초기화
                poisonItemCount = 0;
                mapState = 1; // 맵 상태를 1로 설정
                std::thread portalThread(updatePortals);
                portalThread.detach(); // 스레드를 백그라운드에서 실행합니다.
                continue;
            }
        }

        // 길이가 3보다 작을 때 종료
        if (snakeLength < 3) {
            game_over = true;
            mvprintw(SCREEN_HEIGHT / 2 - 1, SCREEN_WIDTH / 2 - 5, "Game Over");
            mvprintw(SCREEN_HEIGHT / 2, SCREEN_WIDTH / 2 - 12, "Press any key to restart");
            refresh();
            getch();
            game_over = false;
            srand(time(0)); // Re-seed the random number generator for each restart
            initSnake();
            initFood();
            initPoison();
            initDouble();
            initPortals();
            direction = KEY_RIGHT;
            gateCount = 0;
            growthItemCount = 0;  // 먹은 먹이 수 초기화
            poisonItemCount = 0;
            mapState = 1; // 맵 상태를 1로 설정
            std::thread portalThread(updatePortals);
            portalThread.detach(); // 스레드를 백그라운드에서 실행합니다.
            continue;
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
                gateCount += 1;
                initPortals();
            }
        }

        // 먹이 획득
        if (nextX == foodX && nextY == foodY) {
            snakeLength += (doubleActive ? 2 : 1); // 더블 아이템 효과 적용
            initFood();
            growthItemCount += (doubleActive ? 2 : 1); // 더블 아이템 효과 적용
        }

        // 독을 획득
        if (nextX == poisonX && nextY == poisonY) {
            snakeLength -= (doubleActive ? 2 : 1); // 더블 아이템 효과 적용
            initPoison();
            poisonItemCount += (doubleActive ? 2 : 1); // 더블 아이템 효과 적용
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

        if (checkConditionToChangeMap()) {
            if (mapState == 1) {
                mapState = 2;
            } else if (mapState == 2) {
                mapState = 3;
            } else if (mapState == 3) {
                mapState = 4;
            } else if (mapState == 4) {
                mapState = 5;
            } else if(mapState == 5){
                printf("Stage Clear!");
            }
                initSnake();
                gateCount = 0;
                growthItemCount = 0;  // 먹은 먹이 수 초기화
                poisonItemCount = 0;
                snakeLength = 3;
                waitForUserInput();
                drawMap(mapState); // 새로운 맵 상태로 다시 그리기
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