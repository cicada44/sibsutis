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
clean:
	rm $(BUILD)/*
height:
	$(CC) $(FLAGS) $(SRC)/exp.c $(AVL) -o $(BUILD)/height
run_height:
	$(BUILD)/height
run_exp:
	exp/./script
	mv plot.svg $(BUILD)/
	firefox $(BUILD)/plot.svg