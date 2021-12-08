all: plumbing.o
	gcc -o plumbing plumbing.o
plumbing.o: plumbing.c
	gcc -c plumbing.c
run:
	./plumbing
clean:
	rm plumbing
	rm *.o