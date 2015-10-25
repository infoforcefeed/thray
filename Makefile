CPPFLAGS=-std=c++0x -pthread -Wall -Werror -Wshadow -g3 -O2
INCLUDES=-I./include
LIBS=-lstdc++ -lcurl -loauth
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

$(NAME): thray.o main.o
	$(CC) $(CPPFLAGS) $(INCLUDES) -o $(NAME) $^ $(LIBS)

