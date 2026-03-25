TARGET = unit_tests.exe
FLAGS = -std=c++20 -Wall -Werror -Iusr/include -MMD -MP --coverage

LIBS_GOOGLE = -lgtest -lgtest_main -pthread --coverage

SRC = $(wildcard *.cpp)
OBJ = $(patsubst %.cpp, out/%.o, $(SRC))
DEP = $(OBJ:.o=.d)

OUT = out

all : $(TARGET)

$(OUT) :
		mkdir -p out

$(TARGET) : $(OBJ)
		g++ $(OBJ) -o $(TARGET) $(LIBS_GOOGLE)

out/%.o : %.cpp | $(OUT)
		g++ -c $< -o $@ $(FLAGS)

-include $(DEP)

clean :
		rm -rf out
		rm -f $(TARGET)
		rm -f *.txt

.PHONY: clean 
