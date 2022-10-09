all:
	$(CC) -c libmagicm.c -o libmagicm.o -Wall
	$(CC) -c server.c -o server.o -Wall
	$(CC) -c client.c -o client.o -Wall
	$(CC) -c magicm.c -o magicm.o -Wall
	$(CC) magicm.o server.o client.o libmagicm.o -o magicm
clean:
	rm *.o
