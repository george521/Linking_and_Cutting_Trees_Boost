name = program
src = $(wildcard main.cpp)
incl = include
obj = $(src:.c=.o)

Leda = '/usr/local/LEDA/incl'
LedaLibs = '/usr/local/LEDA' 

BOOSTDIR = '/usr/include'

CC = g++

CFLAGS = -std=c++0x -O3 -g 
LIBFLAGS = -lleda -lm



all: $(name)

$(name): $(obj)
	$(CC) $(CFLAGS) -o $@ $^ -I$(Leda) -L$(LedaLibs) -I$(BOOSTDIR) $(LIBFLAGS) 

run:
	./$(name)

clean:
	rm -f $(name)


