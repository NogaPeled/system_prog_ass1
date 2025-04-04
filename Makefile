# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic -g

# Source files
SRCS = Graph.cpp Algorithms.cpp Queue.cpp UnionFind.cpp
OBJS = $(SRCS:.cpp=.o)

# Executables
MAIN_EXEC = Main
TEST_EXEC = test

# Default target
all: $(MAIN_EXEC)

# Main demo build
$(MAIN_EXEC): $(OBJS) Main.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^

# Test build
$(TEST_EXEC): $(OBJS) tests.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^

# Run tests
test: $(TEST_EXEC)
	./$(TEST_EXEC)

# Run with valgrind
valgrind: $(TEST_EXEC)
	valgrind --leak-check=full ./$(TEST_EXEC)

# Clean
clean:
	rm -f *.o $(MAIN_EXEC) $(TEST_EXEC)
