CXX = g++
CXXFLAGS = -std=c++11 -Wall

TARGET = aoc18

SRCDIR = src
INCDIR = inc
SRCS = $(wildcard $(SRCDIR)/*.cpp)
OBJS = $(SRCS:.cpp=.o)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(SRCDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -I$(INCDIR) -c -o $@ $<

.PHONY: clean
clean:
	rm -f $(TARGET) $(OBJS)
