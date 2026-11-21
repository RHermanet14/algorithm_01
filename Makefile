CC = g++
CFLAGS = --std=c++17 -Wall -pedantic -Werror -g -Wno-unused-variable
DEPS = 
OBJECTS = 
PROGRAM = alg1a alg1b generate

.PHONY: all clean lint

all: $(PROGRAM)

%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c $<

alg1a: alg1a.o $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

alg1b: alg1b.o $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

generate: generate_input.o $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm *.o $(PROGRAM)

lint: 
	cpplint *.cpp *.hpp