CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -std=c11 -Iinclude
TARGET = lexicore

SRCS = src/main.c src/dictionary.c src/file_manager.c src/input.c src/statistics.c
OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

valgrind: $(TARGET)
	valgrind --leak-check=full --show-leak-kinds=all ./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all run valgrind clean