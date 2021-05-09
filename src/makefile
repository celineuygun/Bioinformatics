CC=gcc
CFLAGS=-g -O2
LDFLAGS=-lm

DEPS = sequence.h database.h
OBJS = sequence.o database.o main.o

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

main: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm -rf *.o main 
