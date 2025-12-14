CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I../lib
LDFLAGS = 

TARGET = hamming
LIBRARY = libcodec.a

SRC_MAIN = main.cpp
SRC_LIB = ../lib/codec.cpp
OBJ_MAIN = main.o
OBJ_LIB = codec.o

all: $(TARGET)

$(TARGET): $(OBJ_MAIN) $(LIBRARY)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJ_MAIN) -L. -lcodec

$(LIBRARY): $(OBJ_LIB)
	ar rcs $@ $^

$(OBJ_MAIN): $(SRC_MAIN)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_LIB): $(SRC_LIB) ../lib/codec.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ_MAIN) $(OBJ_LIB) $(LIBRARY) $(TARGET)

rebuild: clean all

.PHONY: all clean rebuild