CC = gcc
CFLAGS = -Wall
TARGET = gausianElimination
SRC = main.c
DEBUG_TARGET = $(TARGET)_debug

release: $(SRC)
	$(CC) $(CFLAGS) $^ -o $(TARGET)

debug: $(SRC)
	$(CC) $(CFLAGS) -DDEBUG $^ -o $(DEBUG_TARGET)

.PHONY: clean

clean:
	rm -f $(TARGET) $(DEBUG_TARGET)