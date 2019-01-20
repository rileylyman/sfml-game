CC=g++
CFLAGS=-std=c++11 -I.
SFML_LIBS=-lsfml-graphics -lsfml-window -lsfml-system

SRCS=$(wildcard *.cpp)
OBJ_C=$(patsubst %.cpp, %.o, $(SRCS))

APP_NAME=game

all: sfml-app

%.o: %.cpp
	$(CC) -g -c $< -o $@

depend: .depend

.depend: $(SRCS)
	@echo "Checking dependencies"
	rm -f ./.depend
	$(CC) $(CFLAGS) -MM $^ > ./.depend;

include .depend

sfml-app: $(OBJ_C) depend
	@echo "Building"
	$(CC) -g -o $(APP_NAME) $(OBJ_C) $(SFML_LIBS)

clean:
	@echo "Cleaning"
	$(RM) $(APP_NAME) *.o *.gch