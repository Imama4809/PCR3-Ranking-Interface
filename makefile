CC = gcc
CFLAGS = -Wall -Wextra -g -Iinc

SRC = $(wildcard src/*.c)
OBJ = $(patsubst src/%.c,obj/%.o,$(SRC))

program: $(OBJ)
	$(CC) $(CFLAGS) -o program $(OBJ) -lm

obj/%.o: src/%.c | obj
	$(CC) $(CFLAGS) -c $< -o $@

obj:
	mkdir -p obj

clean:
	rm -f obj/*.o program