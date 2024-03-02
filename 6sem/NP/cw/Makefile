DIRGUARD = @mkdir -p $(@D)

CFLAGS = -Wall -Wextra
CXXFLAGS = -pedantic -std=c++17
CXX = g++

CXXSRC = $(wildcard src/*.cpp)
CXXEXEC = $(patsubst src/%.cpp,bin/%,$(CXXSRC))

.PHONY: all
all: $(CXXEXEC)

bin/%: src/%.cpp
	$(DIRGUARD)
	$(CXX) $(CFLAGS) $(CXXFLAGS) -o $@ $<

.PHONY: clean
.SILENT: clean
clean:
	rm -f $(CXXEXEC)