CC=gcc
CFLAGS=-g -O2

DEPS = sequence.h database.h
OBJS = sequence.o database.o main.o

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

main: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -rf *.o main 