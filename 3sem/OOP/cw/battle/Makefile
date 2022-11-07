SFML_FLAGS=-lsfml-graphics -lsfml-window -lsfml-system

PP=g++

PP_FLAGS=-Wall -Werror -Wextra

BUILD_DIR=build
SRC_DIR=src
COMMON_DIR=$(SRC_DIR)/common
FIGHTER_DIR=$(SRC_DIR)/libfighters
MAIN_DIR=$(SRC_DIR)/main
WINDOW_DIR=$(SRC_DIR)/libwindow

COMPILE_SRC=$(MAIN_DIR)/main.cpp $(FIGHTER_DIR)/Fighter.cpp

all:
	$(PP) $(PP_FLAGS) $(COMPILE_SRC) $(SFML_FLAGS) -o $(BUILD_DIR)/battle

run:
	$(BUILD_DIR)/battle