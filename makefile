CC = g++
CFLAGS = -W -Wall
SRC = draw.cpp game_start.cpp handle.cpp init_state.cpp main.cpp move_snake.cpp run.cpp
OBJ = draw.o game_start.o handle.o init_state.o main.o move_snake.o run.o
PROG = run

all : ${PROG}
${PROG} : ${OBJ}
	${CC} -o ${PROG} ${OBJ}
	rm *.o
${Obj} : ${SRC}
	${CC} ${CFLAGS} -c -o draw.o draw.cpp
	${CC} ${CFLAGS} -c -o game_start.o game_start.cpp
	${CC} ${CFLAGS} -c -o handle.o handle.cpp
	${CC} ${CFLAGS} -c -o init_state.o init_state.cpp
	${CC} ${CFLAGS} -c -o move_snake.o move_snake.cpp
	${CC} ${CFLAGS} -c -o run.o run.cpp
	${CC} ${CFLAGS} -c -o main.o main.cpp
clean :
	rm *.o run