
all: main

main: client.o
	${CC} ${CFLAGS} $^ -o $@

client.o: client.c
	${CC} client.c -c -o $@

clean:
	rm *.o main