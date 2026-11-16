CC = g++
CFLAGS = --std=c++17 -Wall -pedantic -Werror -g -Wno-unused-variable
DEPS = 
OBJECTS = 
PROGRAM = alg01

.PHONY: all clean lint

all: $(PROGRAM)

%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c $<

alg01: main.o $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm *.o $(PROGRAM)

lint: 
	cpplint *.cpp *.hpp