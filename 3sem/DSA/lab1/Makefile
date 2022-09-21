CC = gcc
FLAGS = -Wall -Werror -Wextra
SRC = src
AVL = $(SRC)/AVLTree.c
MAIN = $(SRC)/main.c
BUILD = build

all:
	$(CC) $(FLAGS) $(AVL) $(MAIN) -o $(BUILD)/avltree
run: $(BUILD)/./avltree
	$(BUILD)/./avltree
leaks: $(BUILD)/./avltree
	valgrind $(BUILD)/./avltree
clean: $(BUILD)/./avltree
	rm $(BUILD)/*