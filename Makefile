# CC = g++
# CFLAGS = -std=c++17 --debug
#
# main: main.o my_class.o
# 	$(CC) $(CFLAGS) -o main main.o my_class.o
#
# main.o: main.cpp my_class.cpp my_class.h
# 	$(CC) $(CFLAGS) -c main.cpp
#
# my_class.o: my_class.cpp
all:
	g++ -std=c++17 -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio --debug *.cpp -o sfml-app
