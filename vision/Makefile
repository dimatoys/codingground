DEFAULT_RUN = test2

CC = g++
CFLAGS = 
INCLUDES = bmp.h camera.h
OBJS = bmp.o camera.o

all: run

run: $(DEFAULT_RUN).run
	./$<

%.o: %.c $(INCLUDES)
	$(CC) $(CFLAGS) $(INCLUDES) -c $<  -o $@

%.run: $(OBJS) %.o
	$(CC) -o $@ $^

clean:
	rm *.o *.bmp *.run
