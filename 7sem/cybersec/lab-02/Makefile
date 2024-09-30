CC = gcc
CFLAGS = -g3 -O0 -Wall
LIB = -lm
INCLUDES = -I src/
dirs = ./bin ./obj
main_obj = ./obj/main.o ./obj/encryptolib.o ./obj/extralib.o ./obj/cryptolib.o ./obj/hashtab.o

all: ./bin/main

./bin/main: $(dirs) $(main_obj)
	$(CC) $(main_obj) $(CFLAGS) -o ./bin/cmpl $(LIB)

$(dirs):
	mkdir obj
	mkdir bin

./obj/main.o: ./src/main.c
	gcc -c ./src/main.c -Wall -o ./obj/main.o $(INCLUDES)

./obj/cryptolib.o: ./src/cryptolib.c
	gcc -c ./src/cryptolib.c -Wall -o ./obj/cryptolib.o $(INCLUDES)

./obj/encryptolib.o: ./src/encryptolib.c
	gcc -c ./src/encryptolib.c -Wall -o ./obj/encryptolib.o $(INCLUDES)

./obj/extralib.o: ./src/extralib.c
	gcc -c ./src/extralib.c -Wall -o ./obj/extralib.o $(INCLUDES)

./obj/hashtab.o: ./src/hashtab.c
	gcc -c ./src/hashtab.c -Wall -o ./obj/hashtab.o $(INCLUDES)

.PHONY: clean exec
clean:
	rm -r -f bin/
	rm -r -f obj/

exec:
	make
	./bin/cmpl
