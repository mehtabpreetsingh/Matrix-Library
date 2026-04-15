all:
	gcc -fPIC main.c matrix.c -o main

clean:
	rm -f main
