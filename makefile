all:
	#g++ -std=c++11 -g -o CreateGraphAndTest CreateGraphAndTest.cpp dijkstra.cpp
	g++ -std=c++11 -g -o FindPaths FindPaths.cpp bellman_ford.cpp
	#g++ -std=c++11 -g -o TestRandomGraph TestRandomGraph.cpp dijkstra.cpp disjoint_sets.cc
