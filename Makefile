CXX := g++
CXXFLAGS := -g -Wall -std=c++11 -O3
# SRCS := main.cpp customer.cpp node.cpp solution.cpp mocrosl.cpp 
SRCS := main.cpp Hill_Climbing.cpp Readfile.cpp 
OBJS := $(SRCS:.cpp=.o)

all: main
	
main: $(OBJS)
	$(CXX) $(CXXFLAGS) -o run $(OBJS)
	
$(OBJS) : $(SRCS)

clean:
	rm -rf run $(OBJS)

# help:
# 	@echo "      =========================================="
# 	@echo "        If you want to execute this program."
# 	@echo "        You must follow certain form."
# 	@echo "        i.e. ./mocrosl [dataset] [run] [iteration]"
# 	@echo "      =========================================="
