CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11
LDFLAGS = -lncurses -pthread

TARGET = snake_game
SRCS = main.cpp draw.cpp game_start.cpp handle.cpp init_state.cpp move_snake.cpp run.cpp map.cpp initPortals.cpp stage.cpp game_over.cpp

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS) $(LDFLAGS)

clean:
	rm -f $(TARGET)