GPP = g++
FLAGS = -Wall -Werror -Wextra
SRC = src

DICTS_DIR = Dicts

ALL_SRC = $(SRC)/Hashtab/Hashtab.cpp $(SRC)/Ext_funcs/ext_funcs.cpp $(SRC)/Main/main.cpp
BUILD = build

dbg:
	$(GPP) $(FLAGS) -g -O0 $(ALL_SRC) -o $(BUILD)/dbg

# hashtab:
# 	$(GPP) -DEXP_TIME $(FLAGS) $(ALL_SRC) -o $(BUILD)/ht_exp_time

# dicts
time_exp:
	$(GPP) -D_EXP_TIME $(FLAGS) $(ALL_SRC) -o $(BUILD)/ht_exp_time
	$(BUILD)/ht_exp_time $(DICTS_DIR)/dict1.txt > Data/time.txt
	Plot/exp_time.gp
	mv time.svg Data/time.svg
	firefox Data/time.svg

coll_exp:
	$(GPP) -D_EXP_COLL $(FLAGS) $(ALL_SRC) -o $(BUILD)/ht_exp_coll
	$(BUILD)/ht_exp_coll $(DICTS_DIR)/dict1.txt > Data/coll.txt
	Plot/exp_coll.gp
	mv coll.svg Data/coll.svg
	firefox Data/coll.svg
exp:
	make time_exp && make coll_exp

test:
	$(GPP) $(FLAGS) $(SRC)/Hashtab/Hashtab.cpp $(SRC)/Ext_funcs/ext_funcs.cpp src/Tests/test.cpp -o $(BUILD)/test

run_test:
	$(BUILD)/test

exp_add:
	$(BUILD)/ht_exp $(DICTS_DIR)/dict_exp.txt

clear:
	rm $(BUILD)/*