# define the compiler
CXX			:= g++
OUTPUT	:= spaceshooter

# compiler and linker flags
CXX_FLAGS	:= -O3 -std=c++17
INCLUDES	:= -I./src
LDFLAGS		:= -O3 -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

# source file for the application
SRC_FILES	:= $(wildcard src/*.cpp)
OBJ_FILES	:= $(SRC_FILES:.cpp=.o)

# make
all: $(OUTPUT)

# define the main executable requirements / command
$(OUTPUT):$(OBJ_FILES) Makefile
	$(CXX) $(OBJ_FILES) $(LDFLAGS) -o ./bin/$@

# specification of how the object files are compiled from cpp files
.cpp.o:
	$(CXX) -c $(CXX_FLAGS) $(INCLUDES) $< -o $@

# 'make clean'
clean:
	rm -f $(OBJ_FILES) ./bin/spaceshooter

# 'make run'
run: $(OUTPUT)
	cd bin && ./spaceshooter && cd ..

