CC = gcc
CFLAGS = -Wall -Wextra -g -Iinc

SRC = $(wildcard src/*.c)
OBJ = $(patsubst src/%.c,obj/%.o,$(SRC))


TARGET = run_tests
TEST_SRC = $(wildcard tests/*.c)
OBJ_EXCLUDING_MAIN = $(filter-out obj/main.o, $(OBJ))
CHECK_FLAGS = $(shell pkg-config --cflags --libs check) -lm


program: bin $(OBJ)
	$(CC) $(CFLAGS) -o bin/program $(OBJ) -lm

obj/%.o: src/%.c | obj
	$(CC) $(CFLAGS) -c $< -o $@

obj:
	mkdir -p obj

bin:
	mkdir -p bin

$(TARGET): $(TEST_SRC) $(OBJ)
	$(CC) $(CFLAGS) $(TEST_SRC) $(OBJ_EXCLUDING_MAIN) $(CHECK_FLAGS) -o bin/$(TARGET)

test: $(TARGET)
	./bin/$(TARGET)

clean:
	rm -f obj/*.o bin/*