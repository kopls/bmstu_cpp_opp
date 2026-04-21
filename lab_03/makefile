CXX := g++
CXX_FLAGS := -std=c++20 -Wall -I.
TARGET := app.exe

SRC := $(wildcard *.cpp)
OBJ := $(SRC:.cpp=.o)

$(TARGET) : $(OBJ)
	$(CXX) -o $@ $^

%.o : %.cpp
	$(CXX) $(CXX_FLAGS) -o $@ -c $^

clean :
	rm -f $(TARGET) $(OBJ)


