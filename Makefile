CXX = g++
CXXFLAGS = -std=c++17 -Wall -O3

TARGET = aoc18

SRCDIR = src
INCDIR = inc
OBJDIR = obj
SRCS = $(wildcard $(SRCDIR)/*.cpp)
OBJS = $(SRCS:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -I$(INCDIR) -c -o $@ $<

.PHONY: clean
clean:
	rm -rf $(OBJDIR)
	rm -f $(TARGET)
