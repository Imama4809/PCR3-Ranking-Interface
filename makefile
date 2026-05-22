CC = gcc
CFLAGS = -Wall -Wextra -g -Iinc

SRC = $(wildcard src/*.c)
OBJ = $(patsubst src/%.c,obj/%.o,$(SRC))

program: bin $(OBJ)
	$(CC) $(CFLAGS) -o bin/program $(OBJ) -lm

obj/%.o: src/%.c | obj
	$(CC) $(CFLAGS) -c $< -o $@

obj:
	mkdir -p obj

bin:
	mkdir -p bin

clean:
	rm -f obj/*.o bin/program