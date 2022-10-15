GPP=g++
FLAGS=-Wall -Werror -Wextra
MAIN=main.cpp
HASHTABFUNCS=Hashtab.cpp ext_funcs_hashtab.cpp
BUILD=build

hashtab:
	$(GPP) $(FLAGS) main.cpp $(HASHTABFUNCS) -o $(BUILD)/ht_exp
ex_hashtab:
	$(BUILD)/ht_exp
clear:
	rm $(BUILD)/*