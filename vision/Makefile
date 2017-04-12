DEFAULT_RUN = test3

CC = g++
CFLAGS='-std=c++14'
INCLUDES = bmp.h camera.h utils.h extractor.h
OBJS = bmp.o camera.o utils.o extractor.o

all: run

run: $(DEFAULT_RUN).run
	./$<

%.o: %.c $(INCLUDES)
	$(CC) $(CFLAGS) $(INCLUDES) -c $<  -o $@

%.run: $(OBJS) %.o
	$(CC) -o $@ $^

clean:
	rm *.o *.run
