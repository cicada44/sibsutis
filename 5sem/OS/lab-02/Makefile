DIRGUARD = @mkdir -p $(@D)

CFLAGS = -Wall
CC = gcc
CSRC = $(wildcard src/*.c)
CEXEC = $(patsubst src/%.c,bin/%,$(CSRC))

UNAME = $(shell uname)
ifeq ($(UNAME), Darwin)
	C += -ld_classic
endif

.PHONY: all
all: $(CEXEC)

bin/%: src/%.c
	$(DIRGUARD)
	$(CC) $(CFLAGS) -o $@ $<

.PHONY: clean
.SILENT: clean
clean:
	rm -f $(CEXEC)