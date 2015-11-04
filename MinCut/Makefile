CXX = g++
CPPFLAGS = -std=c++11 -O3 -Wall -Werror

karger: Karger.o Graph.o
	$(CXX) $(CPPFLAGS) -o Karger Karger.o Graph.o

Karger.o: Karger.cpp

Graph.o: Graph.cpp

clean:
	@rm *.o Karger
