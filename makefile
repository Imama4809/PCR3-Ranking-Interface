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

$(TARGET): bin $(TEST_SRC) $(OBJ)
	$(CC) $(CFLAGS) $(TEST_SRC) $(OBJ_EXCLUDING_MAIN) $(CHECK_FLAGS) -o bin/$(TARGET)

test: $(TARGET)
	./bin/$(TARGET)

clean:
	rm -rf obj/*.o bin/*
	rm -f asan_obj/*.o bin/*_asan

# ---- AddressSanitizer build ----
ASAN_FLAGS = -fsanitize=address -fno-omit-frame-pointer
ASAN_OBJ = $(patsubst src/%.c,asan_obj/%.o,$(SRC))
ASAN_OBJ_EXCLUDING_MAIN = $(filter-out asan_obj/main.o, $(ASAN_OBJ))
ASAN_TARGET = run_tests_asan

asan_obj:
	mkdir -p asan_obj

asan_obj/%.o: src/%.c | asan_obj
	$(CC) $(CFLAGS) $(ASAN_FLAGS) -c $< -o $@

$(ASAN_TARGET): bin $(TEST_SRC) $(ASAN_OBJ)
	$(CC) $(CFLAGS) $(ASAN_FLAGS) $(TEST_SRC) $(ASAN_OBJ_EXCLUDING_MAIN) $(CHECK_FLAGS) -o bin/$(ASAN_TARGET)

test-asan: $(ASAN_TARGET)
	./bin/$(ASAN_TARGET)

.PHONY: program test clean asan_obj test-asan