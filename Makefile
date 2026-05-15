CC = gcc

CFLAGS = -Wall -Wextra -Iinclude

SRC = src/main.c \
      src/rent.c \
      src/database.c \
      src/export.c \
      src/utils.c

OUT = rentdb

all:
	$(CC) $(SRC) $(CFLAGS) -o $(OUT)

run:
	./$(OUT)

clean:
	rm -f $(OUT)

rebuild: clean all
