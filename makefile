cppflag = -ldl -Wall -Wextra -pedantic

all: test

test: test.o
	g++ $(cppflag) test.o -o test

test.o: Deque.hpp test.cpp
	g++ $(cppflag) -c test.cpp -o test.o

run: all
	./test

clean:
	rm -rf ./test *.o

memcheck:
	valgrind ./test
