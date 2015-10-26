CPPFLAGS=-std=c++0x -pthread -Wall -Werror -Wshadow -g3 -O0 `pkg-config --cflags libxml-2.0`
INCLUDES=-I./include
LIBS=-lstdc++ -lcurl -lxml2 `pkg-config --libs libxml-2.0`
NAME=thray
ifndef CC
	CC=gcc
endif

all: $(NAME)

clean:
	rm *.o
	rm $(NAME)

%.o: ./src/%.c
	$(CC) $(CPPFLAGS) $(INCLUDES) -fpic -c $<

%.o: ./src/%.cpp
	$(CC) $(CPPFLAGS) $(INCLUDES) -fpic -c $<

$(NAME): json11.o thray.o main.o
	$(CC) $(CPPFLAGS) $(INCLUDES) -o $(NAME) $^ $(LIBS)

