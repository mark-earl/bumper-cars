CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra
LDFLAGS = -lpthread -lstdc++

SRCS = main.cpp Car.cpp Rider.cpp
OBJS = $(SRCS:.cpp=.o)

TARGET = bumper_cars.out

all: $(TARGET) clean

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f $(OBJS)
