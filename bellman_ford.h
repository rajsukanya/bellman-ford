#ifndef BELLMAN_FORD_H
#define BELLMAN_FORD_H

#include <cfloat>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

template<typename Out>
void split(const string &s, char delim, Out result);
vector<string> split(const string &s, char delim);
map<int, map<int, int> > load_graph(const string &graph_filename);
void view_graph(map<int, map<int, int> > graph);
bool bellman_ford(map<int, map<int, int> > graph, int w, int s, int u, int v, map<int, vector<int> > &dd, map<int, int> &d, map<int, int> &pi, map<int, int>&q);
void view_bellman_ford_solution(map<int, vector<int> > &dd);

#endif
