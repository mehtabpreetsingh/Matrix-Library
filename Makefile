all: static dynamic

# 1. Create Static Library (.a)
static: matrix.c matrix.h
	gcc -Wall -c matrix.c -o matrix.o
	ar rcs libmatrix.a matrix.o
	gcc -Wall main.c -L. -lmatrix -o main_static -lm

# 2. Create Shared Library (.so)
dynamic: matrix.c matrix.h
	gcc -Wall -fPIC -c matrix.c -o matrix.o
	gcc -shared -o libmatrix.so matrix.o
	gcc -Wall main.c -L. -lmatrix -o main_dynamic -lm
clean:
	rm -f *.o *.so *.a $(TARGET)_static $(TARGET)_dynamic
