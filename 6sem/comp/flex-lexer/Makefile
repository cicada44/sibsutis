DIRGUARD = @mkdir -p $(@D)

BIN = bin
OBJ = obj
SRC = src

HEADERSDIR = $(SRC)
FLEXDIR = /usr/local/Cellar/flex/2.6.4_2

CFLAGS = -Wall
CXX = g++
FLEXXX = $(FLEXDIR)/bin/flex++

LEXERFLEX = $(SRC)/CoolLexer.flex
DRIVER = $(SRC)/driver.cpp

LEXERCPP = $(OBJ)/CoolLexer.cpp
EXE = $(BIN)/driver

.PHONY: all
all: $(EXE)
$(EXE): $(DRIVER) $(LEXERCPP)
	$(DIRGUARD)
	$(CXX) $(CFLAGS) $^ -L$(FLEXDIR)/lib -I$(FLEXDIR)/include -I$(HEADERSDIR) -o $@

.PHONY: $(LEXERCPP)
$(LEXERCPP): $(LEXERFLEX)
	$(DIRGUARD)
	$(FLEXXX) -o $@ $<

.PHONY: clean
.SILENT: clean
clean:
	rm -rf $(BIN) $(OBJ)