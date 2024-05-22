DIRGUARD = @mkdir -p $(@D)

BIN = bin
OBJ = obj
SRC = src

CFLAGS = -Wall
CC = gcc

INFIXY = $(SRC)/infixcalc.y
INFIXC = $(OBJ)/infixcalc.c
INFIXEXE = $(BIN)/infixcalc

POSTFIXY = $(SRC)/rpcalc.y
POSTFIXC = $(OBJ)/rpcalc.c
POSTFIXEXE = $(BIN)/rpcalc

.PHONY: all
all: $(INFIXEXE) $(POSTFIXEXE)

$(INFIXEXE): $(INFIXC)
	$(DIRGUARD)
	$(CC) $(CFLAGS) $^ -o $@ -lm

$(POSTFIXEXE): $(POSTFIXC)
	$(DIRGUARD)
	$(CC) $(CFLAGS) $^ -o $@ -lm

.PHONY: $(INFIXC)
$(INFIXC): $(INFIXY)
	$(DIRGUARD)
	bison -o $@ $<

.PHONY: $(POSTFIXC)
$(POSTFIXC): $(POSTFIXY)
	$(DIRGUARD)
	bison -o $@ $<

.PHONY: clean
.SILENT: clean
clean:
	rm -rf $(BIN) $(OBJ)