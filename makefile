# Makefile for building k-ary tree visualization and tests

CXX = clang++
CXXFLAGS = -std=c++14 -Werror -Wsign-conversion -g
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system
VALGRIND_FLAGS = -v --leak-check=full --show-leak-kinds=all --error-exitcode=99

# Source and object files
DEMOSOURCES = Node.hpp Tree.hpp Demo.cpp
TESTSOURCES = Node.hpp Tree.hpp TestCounter.cpp Test.cpp Complex.cpp
COMPLEXSOURCES = Node.hpp Tree.hpp Complex.cpp ComplexDemo.cpp
COMPLEXOBJECTS = $(subst .cpp,.o,$(filter %.cpp,$(COMPLEXSOURCES)))
DEMOOBJECTS = $(subst .cpp,.o,$(filter %.cpp,$(DEMOSOURCES)))
TESTOBJECTS = $(subst .cpp,.o,$(filter %.cpp,$(TESTSOURCES)))


.PHONY: all run demo test tidy valgrind clean

# Default target to build demo and test
all: demo complex test

# Run tests
run: test
	./test

# Build demo executable
demo: $(DEMOOBJECTS)
	$(CXX) $(CXXFLAGS) $^ $(LDFLAGS) -o demo

# Build test executable
test: $(TESTOBJECTS)
	$(CXX) $(CXXFLAGS) $^ $(LDFLAGS) -o test

# Build complex executable
complex: $(COMPLEXOBJECTS)
	$(CXX) $(CXXFLAGS) $^ $(LDFLAGS) -o complex

# Tidy up the code with clang-tidy
tidy:
	clang-tidy $(filter %.cpp,$(DEMOSOURCES)) -checks=bugprone-*,clang-analyzer-*,cppcoreguidelines-*,performance-*,portability-*,readability-*,-cppcoreguidelines-pro-bounds-pointer-arithmetic,-cppcoreguidelines-owning-memory --warnings-as-errors=-* --

# Run valgrind to check for memory leaks
valgrind: demo test
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./demo
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./test

# Rule to compile source files to object files
%.o: %.cpp %.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up the build artifacts
clean:
	rm -f *.o demo test complex
