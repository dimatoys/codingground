DEFAULT_RUN = test4

CC = g++
CPPFLAGS=-std=c++14
INCLUDES = bmp.h camera.h utils.h extractor.h
OBJS = bmp.o camera.o utils.o extractor.o

all: run

run: $(DEFAULT_RUN).run
	./$<

%.o: %.cpp $(INCLUDES)
	$(CC) $(CPPFLAGS) -c $<  -o $@

%.run: $(OBJS) %.o
	$(CC) -o $@ $^

clean:
	rm *.o *.run
