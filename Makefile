
all: main

main: main.o
	${CC} ${CFLAGS} $^ -o $@

main.o: main.c
	${CC} main.c -c -o $@
