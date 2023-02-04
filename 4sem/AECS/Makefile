CC = gcc
FLAGS = -Wall -Wextra -Werror -pedantic

BUILD_DIR = build
SRC_DIR = src
TEST_DIR = test

OBJ_DIR = obj
LIB_DIR = $(BUILD_DIR)/lib
OBJ_SRC_DIR = $(BUILD_DIR)/$(OBJ_DIR)/$(SRC_DIR)
OBJ_TEST_DIR = $(BUILD_DIR)/$(OBJ_DIR)/$(TEST_DIR)
EXE_DIR = $(BUILD_DIR)/exe

LIBCOMP_DIR = $(SRC_DIR)/libcomputer
MAIN_DIR = $(SRC_DIR)/app

.PHONY: computer.o libcomputer.a main.o app all

all: computer.o libcomputer.a main.o app

app: $(OBJ_SRC_DIR)/main.o $(LIB_DIR)/libcomputer.a
	$(CC) $(FLAGS) -o $(EXE_DIR)/$@ $^

main.o: $(MAIN_DIR)/main.c
	$(CC) -I src -c $(FLAGS) -o $(OBJ_SRC_DIR)/$@ $<

libcomputer.a: $(OBJ_SRC_DIR)/computer.o
	ar rcs $(LIB_DIR)/$@ $^

computer.o: $(LIBCOMP_DIR)/comp.c
	$(CC) -I src -c $(FLAGS) -o $(OBJ_SRC_DIR)/$@ $<

run: $(EXE_DIR)/app
	$(EXE_DIR)/app

# TEST

.PHONY: all test.o main_test.o test_app test

test: all test.o main_test.o test_app

test_app: $(OBJ_TEST_DIR)/test.o $(OBJ_TEST_DIR)/main_test.o $(LIB_DIR)/libcomputer.a
	$(CC) $(FLAGS) -o $(EXE_DIR)/$@ $^

main_test.o: $(TEST_DIR)/main.c
	$(CC) $(FLAGS) -I thirdparty -I src -c -o $(OBJ_TEST_DIR)/$@ $<

test.o: $(TEST_DIR)/test.c
	$(CC) $(FLAGS) -I thirdparty -I src -c -o $(OBJ_TEST_DIR)/$@ $<

run_test: $(EXE_DIR)/test_app
	$(EXE_DIR)/test_app


# CLEAN

clean:
	rm -rf build/lib/* build/exe/* build/obj/*/*
