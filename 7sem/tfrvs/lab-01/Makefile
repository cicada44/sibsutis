DIRGUARD = @mkdir -p $(@D)

CFLAGS = -Wall
CXX = mpicxx
CXXFLAGS = -pedantic -std=c++17
CXXSRC = $(wildcard src/*.cpp)
EXEC = $(patsubst src/%.cpp,bin/%,$(CXXSRC))
CXXEXEC = $(EXEC)

UNAME = $(shell uname)
ifeq ($(UNAME), Darwin)
	CXXFLAGS += -ld_classic
endif

.PHONY: all
all: $(CXXEXEC)

bin/%: src/%.cpp
	$(DIRGUARD)
	$(CXX) $(CFLAGS) $(CXXFLAGS) -o $@ $<

.PHONY: clean
.SILENT: clean
clean:
	rm -f $(CXXEXEC)