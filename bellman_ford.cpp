#include <algorithm>
#include <bits/stdc++.h>
#include <climits>
#include <iomanip>
#include <iterator>
#include <limits>
#include <sstream>
#include "dijkstra.h"

using namespace std;

template<typename Out>
void split(const string &s, char delim, Out result)
{
  string item;
  stringstream ss(s);
  while(getline(ss, item, delim))
  {
    *(result++) = item;
  }
}

vector<string> split(const string &s, char delim)
{
  vector<string> elements;
  split(s, delim, back_inserter(elements));
  return elements;
}

map<int, map<int, double> > load_graph(const string &graph_filename)
{
  map<int, map<int, double> > graph;
  ifstream graph_inStream;
  graph_inStream.open(graph_filename.c_str());
  if(graph_inStream.fail())
  {
    cout << "Failed to open graph text file" << endl;
    exit(1);
  }
  string str, line;
  int num_vertices;
  graph_inStream >> num_vertices;
  char *ch;
  while(getline(graph_inStream, str))
  {
    if(str.length()==0) continue;
    map<int, double> adj_list;
    vector<string> line = split(str, ' ');
    vector<double> row;
    ch = const_cast<char*>(line[0].c_str());
    int v0 = atoi(ch);
    int v;
    double w;
    for(vector<string>::iterator it = next(line.begin()); it != line.end(); it++)
    {
      ch = const_cast<char*>((*it).c_str());
      v = atoi(ch);
      it = next(it);
      ch = const_cast<char*>((*it).c_str());
      w = atof(ch);
      adj_list.insert(pair<int, double>(v, w));
    }
    graph.insert(pair<int, map<int, double> >(v0, adj_list));
  }
  graph_inStream.close();
  return graph;
}
/*
bool has_edge(map<int, map<int, double> > graph, int v1, int v2)
{
  map<int, map<int, double> >::iterator adj_list = graph.find(v1); 
  if(adj_list != graph.end())
  {
    map<int, double>::iterator w = adj_list->second.find(v2);
    if(w != adj_list->second.end())
    {
      return true;
    }
    else 
    {
      return false;
    }
  }
  return false;
}

void add_edge(map<int, map<int, double> > &graph, int v1, int v2)
{
  map<int, map<int, double> >::iterator adj_list = graph.find(v1);
  if(adj_list != graph.end())
  {
    adj_list->second.insert(pair<int, double>(v2, 1.0));
  }
  else
  {
    map<int, double> new_list;
    new_list.insert(pair<int, double>(v2, 1.0));
    graph.insert(pair<int, map<int, double> >(v1, new_list));
  }
}

bool is_connected(map<int, map<int, double> > graph){
  return false;
}

int get_min_degree(map<int, map<int, double> > graph, int max_nodes){
  int min = max_nodes;
  map<int, map<int, double> >::iterator it;
  for(it = graph.begin(); it != graph.end(); it++)
  {
    if(it->second.size() < min)
    {
      min = it->second.size();
    }
  }
  return min;
}

int get_max_degree(map<int, map<int, double> > graph){
  int max = 0;
  map<int, map<int, double> >::iterator it;
  for(it = graph.begin(); it != graph.end(); it++)
  {
    if(it->second.size() > max)
    {
      max = it->second.size();
    }
  }
  return max;
}

double get_avg_degree(map<int, map<int, double> > graph){
  double sum = 0.0;
  double n = 0.0;
  map<int, map<int, double> >::iterator it;
  for(it = graph.begin(); it != graph.end(); it++)
  {
    sum += it->second.size();
    n++;
  }
  return sum/n;
}
*/
void view_graph(map<int, map<int, double> > graph)
{
  map<int, map<int, double> >::iterator it;
  for(it = graph.begin(); it != graph.end(); it++)
  {
    map<int, double>::iterator it2;
    cout << it->first << ": ";
    for(it2 = (*it).second.begin(); it2 != (*it).second.end(); it2++)
    {
      cout << "(" << it2->first << "," << it2->second << ")";
    }
    cout << endl;
  }
}
/*
double get_weight(map<int, map<int, double> > graph, int v1, int v2)
{
  map<int, map<int, double> >::iterator adj_list = graph.find(v1);
  if(adj_list != graph.end())
  {
    map<int, double>::iterator w = adj_list->second.find(v2);
    if(w != adj_list->second.end())
    {
      return w->second;
    }
    else 
    {
      return DBL_MAX;
    }
  }
  return DBL_MAX;
}
*/
void initialize_single_source(map<int, map<int, int> > graph, int s, map<int, int> &d, map<int, int> &pi)
{
  for(map<int, map<int, int> >::iterator it = graph.begin(); it != graph.end(); it++){
    d[it->first] = INT_MAX;
    pi[it->first] = INT_MAX;
  }
  d[s] = 0;
  pi[s] = INT_MAX;
}
/*
void view_d(map<int, double> d)
{
  cout << "d:\n";
  for(map<int, double>::iterator it = d.begin(); it != d.end(); it++)
  {
    cout << it->first << "," << it->second << endl;
  }
}

void view_pi(map<int, int> pi)
{
  cout << "pi:\n";
  for(map<int, int>::iterator it = pi.begin(); it != pi.end(); it++)
  {
    cout << it->first << "," << it->second << endl;
  }
}
*/

void relax(int u, int v, int w, map<int, map<int, int> > graph, map<int, int> &d, map<int, int> &pi, map<int, int> &q)
{
  int du = d[u];
  int dv = d[v];
  map<int, map<int, int> >::iterator u_list = graph.find(u);
  int w_uv = INT_MAX;
  if(u_list != graph.end())
  {
    map<int, int>::iterator w_v = u_list->second.find(v);
    if(w_v != u_list->second.end())
    {
      w_uv = w_v->second;
    }
  }
  if(dv > du + w_uv)
  {
    d[v] = du + w_uv;
    q[v] = du + w_uv;
    pi[v] = u;
  }
}

void relax_with_history(int u, int v, int w, map<int, vector<int> > &dd, map<int, int> &d, map<int, int> &pi, map<int, int> &q)
{
  relax(u, v, w, dd, d, pi, q);
  /*
  for(map<int, vector<int> >::iterator it = dd.begin(); it != dd.end(); it++)
  {
    for()
    {
      //dd[v].insert(d[v]);
    }
  }
  */
}

bool bellman_ford(map<int, map<int, int> > graph, int w, int s, int u, int v, map<int, int> &d, map <int, int> &pi, map<int, int> &q)
{
  initialize_single_source(graph, s, d, pi);
  for(map<int, map<int, int> >::iterator it = graph.begin(); it != graph.end(); it++)
  {
    u = it->first;
    for(map<int, int>::iterator it2 = it->second.begin(); it2 != it->second.end(); it2++)
    {
      v = it2->first;
      w = it2->second;
      relax_with_history(u, v, w, graph, d, pi, q);
    }
  }
  for(map<int, int>::iterator it2 = it->second.begin(); it2 != it->second.end(); it2++)
  {
    if(d[v] > d[u] + INT_MAX)
      return false;
  }
  return true; 
}

