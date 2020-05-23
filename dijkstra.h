#ifndef DIJKSTRA_H
#define DIJKSTRA_H

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
map<int, map<int, double> > load_graph(const string &graph_filename);
bool has_edge(map<int, map<int, double> > graph, int v1, int v2);
void add_edge(map<int, map<int, double> > &graph, int v1, int v2);
bool is_connected(map<int, map<int, double> > graph);
int get_num_vertices(map<int, map<int, double> > graph);
int get_num_edges(map<int, map<int, double> > graph);
int get_min_degree(map<int, map<int, double> > graph, int max_nodes);
int get_max_degree(map<int, map<int, double> > graph);
double get_avg_degree(map<int, map<int, double> > graph);


void view_graph(map<int, map<int, double> > graph);
double get_weight(map<int, map<int, double> > graph, int v1, int v2);
void dijkstra(map<int, map<int, double> > graph, int s, map<int, double> &d, map<int, int> &pi);
void dijkstra_traceback(map<int, double> &d, map<int, int> &pi, int s, int u, vector<int> &P, double &C);

#endif
