GPP = g++
FLAGS = -Wall -Werror -Wextra
SRC = src

DICTS_DIR = Dicts

ALL_SRC = $(SRC)/Hashtab/Hashtab.cpp $(SRC)/Ext_funcs/ext_funcs.cpp $(SRC)/Main/main.cpp
BUILD = build

dbg:
	$(GPP) $(FLAGS) -g -O0 $(ALL_SRC) -o $(BUILD)/dbg

hashtab:
	$(GPP) $(FLAGS) $(ALL_SRC) -o $(BUILD)/ht_exp

# dicts
run_dict_1:
	$(BUILD)/ht_exp $(DICTS_DIR)/dict1.txt
run_dict_2:
	$(BUILD)/ht_exp ../$(DICTS_DIR)/dict2.txt
run_dict_3:
	$(BUILD)/ht_exp ../$(DICTS_DIR)/dict3.txt
exp_add:
	$(BUILD)/ht_exp $(DICTS_DIR)/dict_exp.txt

clear:
	rm $(BUILD)/*