CC=gcc
CFLAGS=-Wall -g
OBJS=main.o disk.o cache.o fs_core.o utils.o

all: minifs

minifs: $(OBJS)
	$(CC) -o minifs $(OBJS)

clean:
	rm -f *.o minifs
