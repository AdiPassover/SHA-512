CXX=clang++
CXXFLAGS=-std=c++14 -Werror -Wsign-conversion

SRC = sha512_utils/sha512.cpp sha512_utils/logical_functions.cpp sha512_utils/preprocessing.cpp
OBJ = $(SRC:.cpp=.o)
TARGET = main

.PHONY: all clean python_test

all: $(TARGET)

$(TARGET): $(OBJ) $(TARGET).cpp
	$(CXX) $(CXXFLAGS) -o $@ $^

$(OBJ): %.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

python_test: $(TARGET)
	python3 tests/python_tests.py -n 1000

clean:
	rm -f $(OBJ) $(TARGET)

