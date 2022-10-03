SRC = src
FLAGS = -Wall -Wwrite-strings -Wextra
DOT = tPoint.hpp
FIELD = Field.hpp
MAIN = main.cpp
PP = g++
F_GRAPH = -lgraph
MOV_DOTS = moving_dots.cpp
BUILD = build

dots:
	$(PP) $(SRC)/$(MOV_DOTS) $(F_GRAPH) -o $(BUILD)/dots
dots_run:
	$(BUILD)/dots
dots_clean:
	rm $(BUILD)/dots
clean:
	rm $(BUILD)/*
figures:
	$(PP) $(FLAGS) $(SRC)/$(MAIN) $(F_GRAPH) -o $(BUILD)/figures
figures_run:
	$(BUILD)/figures
figures_clean:
	rm $(BUILD)/figures