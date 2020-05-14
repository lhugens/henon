INCLUDES=-I/opt/local/include
LIBS=-L/opt/local/lib -lgmp -lmpfr
FLAGS=-std=c++11 -Wall
ALL=$(INCLUDES) $(LIBS) $(FLAGS)
CC=g++
OBJECT=henon.cpp
TARGET=henon

all: compile run

compile:
	$(CC) $(ALL) $(OBJECT) -o $(TARGET)
run:
	./henon 1000
