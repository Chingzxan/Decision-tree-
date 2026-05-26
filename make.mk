CC = gcc
CFLAGS = -Wall -Wextra -O2 -g
TARGET = robot
OBJ = tree.o beging.o Smeshariki.o

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

tree.o: tree.c tree.h
	$(CC) $(CFLAGS) -c $< -o $@

beging.o: beging.c beging.h tree.h
	$(CC) $(CFLAGS) -c $< -o $@

Smeshariki.o: Smeshariki.c beging.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean