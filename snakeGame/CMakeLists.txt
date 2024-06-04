cmake_minimum_required(VERSION 3.0)
project(snake_game2)

# 헤더 파일과 소스 파일 경로 설정
include_directories(header)

# 소스 파일 목록
set(SOURCES 
    draw.cpp
    game_start.cpp
    handle.cpp
    init_state.cpp
    move_snake.cpp
    run.cpp
    main.cpp
)

# 실행 파일 생성
add_executable(SnakeGame ${SOURCES})

target_link_libraries(SnakeGame ncurses)
