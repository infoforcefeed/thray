CPPFLAGS=-std=c++0x -pthread -Wall -Werror -Wshadow -g3 -O2
INCLUDES=-I./include
LIBS=-lstdc++
NAME=thray
CC=clang++

all: $(NAME)

clean:
	rm *.o
	rm $(NAME)

%.o: ./src/%.c
	$(CC) $(CPPFLAGS) $(INCLUDES) -fpic -c $<

%.o: ./src/%.cpp
	$(CC) $(CPPFLAGS) $(INCLUDES) -fpic -c $<

$(NAME): main.o
	$(CC) $(CPPFLAGS) $(INCLUDES) -o $(NAME) $^ $(LIBS)

