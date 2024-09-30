CC = gcc
CFLAGS = -g3 -O0 -Wall
LIB = -lm
INCLUDES = -I src/
dirs = ./bin ./obj
main_obj = ./obj/main.o ./obj/extralib.o ./obj/dsignlib.o ./obj/md5.o

all: ./bin/main

./bin/main: $(dirs) $(main_obj)
	$(CC) $(main_obj) $(CFLAGS) -o ./bin/cmpl $(LIB)

$(dirs):
	mkdir obj
	mkdir bin

./obj/main.o: ./src/main.c
	gcc -c ./src/main.c -Wall -o ./obj/main.o $(INCLUDES)

./obj/dsignlib.o: ./src/dsignlib.c
	gcc -c ./src/dsignlib.c -Wall -o ./obj/dsignlib.o $(INCLUDES)

./obj/md5.o: ./src/md5.c
	gcc -c ./src/md5.c -Wall -o ./obj/md5.o $(INCLUDES)

./obj/extralib.o: ./src/extralib.c
	gcc -c ./src/extralib.c -Wall -o ./obj/extralib.o $(INCLUDES)

.PHONY: clean exec
clean:
	rm -r -f bin/
	rm -r -f obj/

exec:
	make
	./bin/cmpl
