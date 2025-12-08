CXX           = clang++
OP            = -funsafe-math-optimizations  -O2 -flto -pipe -march=native -DDEBUG
CXXFLAGS      = -std=c++17 -Wall -Wextra -ferror-limit=1 -ftemplate-backtrace-limit=0 $(OP)
LFLAGS        = $(OP)


LINK          = $(CXX)



####### Output directory
OBJECTS_DIR   = ./obj
BIN_DIR       = ./bin
LIB_DIR       = .
LOG_DIR       = .

all: test


test: tests/test.cc
	$(CXX) -c $(CXXFLAGS) -o $(OBJECTS_DIR)/test_test.o tests/test.cc
	$(LINK) -o $(BIN_DIR)/test_test $(OBJECTS_DIR)/test_test.o $(LFLAGS)


clean:
	rm -rf $(OBJECTS_DIR)/*
	rm -rf $(BIN_DIR)/*

