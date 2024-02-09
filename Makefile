# Compiler settings
CXX = g++-13

# Source files
SRCS = course_database.cpp main.cpp student_database.cpp student.cpp swap_list.cpp system.cpp wait_list.cpp course.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Target executable
TARGET = main

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)