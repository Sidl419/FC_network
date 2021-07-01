PROG = matrix_test
CFLAGS = -g -Wall -fsanitize=address -fno-omit-frame-pointer
CC = g++

$(PROG): main.cpp matrix.o
	$(CC) $(CFLAGS) -c matrix.cpp -o matrix.o
	$(CC) $(CFLAGS) main.cpp matrix.o -o $(PROG)
clean:
	rm -f *.o $(PROG)
test: main.cpp matrix.o
	$(CC) $(CFLAGS) -c matrix.cpp -o matrix.o
	$(CC) $(CFLAGS) main.cpp matrix.o -o $(PROG)
	./$(PROG) test