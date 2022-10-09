all:
	$(CC) -c libmagicm/user.c -o user.o -Wall
	$(CC) -c server.c -o server.o -Wall
	$(CC) -c client.c -o client.o -Wall
	$(CC) -c magicm.c -o magicm.o -Wall
	$(CC) magicm.o server.o client.o user.o -o magicm
clean:
	rm *.o
