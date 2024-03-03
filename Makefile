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
	g++ -std=c++17 --debug main.cpp Vec2.cpp -o main.out
