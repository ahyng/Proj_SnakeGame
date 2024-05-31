CC = g++
CFLAGS = -W -Wall -I/home/seungwan/Proj_SnakeGame #헤더파일 경로에 맞게 수정

SRC = draw.cpp game_start.cpp handle.cpp init_state.cpp main.cpp init_portals.cpp move_snake.cpp run.cpp map.cpp stage.cpp game_over.cpp
OBJ = draw.o game_start.o handle.o init_state.o main.o init_portals.o move_snake.o run.o map.o stage.o game_over.o
PROG = run

all : ${PROG}

${PROG} : ${OBJ}
	${CC} -o ${PROG} ${OBJ} -lncurses
	rm *.o

${OBJ} : ${SRC}
	${CC} ${CFLAGS} -c -o draw.o draw.cpp
	${CC} ${CFLAGS} -c -o game_start.o game_start.cpp
	${CC} ${CFLAGS} -c -o handle.o handle.cpp
	${CC} ${CFLAGS} -c -o init_state.o init_state.cpp
	${CC} ${CFLAGS} -c -o move_snake.o move_snake.cpp
	${CC} ${CFLAGS} -c -o init_portals.o init_portals.cpp
	${CC} ${CFLAGS} -c -o map.o map.cpp
	${CC} ${CFLAGS} -c -o stage.o stage.cpp
	${CC} ${CFLAGS} -c -o game_over.o game_over.cpp
	${CC} ${CFLAGS} -c -o run.o run.cpp
	${CC} ${CFLAGS} -c -o main.o main.cpp

clean :
	rm *.o run