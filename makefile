# @file makefile
#
# makefile for the bumper cars project

# g++, C++ 11, pthreads, turn on warnings
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra
LDFLAGS = -lpthread

# Source files
SRCS = main.cpp Car.cpp Rider.cpp output.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Executable
TARGET = bumper_cars.out

# `make`
all: $(TARGET) clean

# Compiling
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Creating object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

# Clean, (remove object files)
clean:
	rm -f $(OBJS)
