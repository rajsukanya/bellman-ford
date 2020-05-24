#include <algorithm>
#include <bits/stdc++.h>
#include <climits>
#include <iomanip>
#include <iterator>
#include <limits>
#include <sstream>
#include "bellman_ford.h"

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

map<int, map<int, int> > load_graph(const string &graph_filename)
{
  map<int, map<int, int> > graph;
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
    map<int, int> adj_list;
    vector<string> line = split(str, ' ');
    vector<int> row;
    ch = const_cast<char*>(line[0].c_str());
    int v0 = atoi(ch);
    int v, w;
    for(vector<string>::iterator it = next(line.begin()); it != line.end(); it++)
    {
      ch = const_cast<char*>((*it).c_str());
      v = atoi(ch);
      it = next(it);
      ch = const_cast<char*>((*it).c_str());
      w = atof(ch);
      adj_list.insert(pair<int, int>(v, w));
    }
    graph.insert(pair<int, map<int, int> >(v0, adj_list));
  }
  graph_inStream.close();
  return graph;
}

void view_graph(map<int, map<int, int> > graph)
{
  map<int, map<int, int> >::iterator it;
  for(it = graph.begin(); it != graph.end(); it++)
  {
    map<int, int>::iterator it2;
    cout << it->first << ": ";
    for(it2 = (*it).second.begin(); it2 != (*it).second.end(); it2++)
    {
      cout << "(" << it2->first << "," << it2->second << ")";
    }
    cout << endl;
  }
}

void initialize_single_source(map<int, map<int, int> > graph, int s, map<int, int> &d, map<int, int> &pi, map<int, vector<int> > &dd)
{
  vector<int> infinity;
  infinity.push_back(INT_MAX);
  for(map<int, map<int, int> >::iterator it = graph.begin(); it != graph.end(); it++){
    d[it->first] = INT_MAX;
    pi[it->first] = INT_MAX;
    dd[it->first] = infinity;
  }
  d[s] = 0;
  pi[s] = INT_MAX;
}

void view_d(map<int, int> d)
{
  cout << "d:\n";
  for(map<int, int>::iterator it = d.begin(); it != d.end(); it++)
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

void relax(int u, int v, int w, map<int, int> &d, map<int, int> &pi)
{
  cout << "relax: " << u << ", " << v << ", " << w << ", " << d[v] << ", " << d[u] << endl;
  if(d[u]!=INT_MAX){
    if(d[v] > d[u] + w){
      cout << "updating d[v] " << d[v] << " with " << d[u]+w << endl;
      d[v] = d[u] + w;
      pi[v] = u;
      cout << "now: d[" << v << "]=" << d[v] << endl;
    }
  }
}

void relax_with_history(int u, int v, int w, map<int, vector<int> > &dd, map<int, int> &d, map<int, int> &pi)
{
  relax(u, v, w, d, pi);
  dd[u].push_back(d[u]);
}

bool bellman_ford(map<int, map<int, int> > graph, int s, map<int, vector<int> > &dd)
{
  int u, v, w;
  map<int, int> d, pi;
  initialize_single_source(graph, s, d, pi, dd);
  for(map<int, map<int, int> >::iterator it = graph.begin(); it != graph.end(); it++)
  {
    u = it->first;
    for(map<int, int>::iterator it2 = it->second.begin(); it2 != it->second.end(); it2++)
    {
      v = it2->first;
      w = it2->second;
      cout << u << ", " << v << ", " << w << endl;
      relax_with_history(u, v, w, dd, d, pi);
    }
  }
  for(map<int, map<int, int> >::iterator it = graph.begin(); it != graph.end(); it++)
  {
    u = it->first;
    for(map<int, int>::iterator it2 = it->second.begin(); it2 != it->second.end(); it2++)
    {
      v = it2->first;
      w = it2->second;
      if(d[v] > d[u] + w){
        return false;
      }
    }
  }
  return true; 
}

void view_bellman_ford_solution(map<int, vector<int> > &dd)
{
  for(map<int, vector<int> >::iterator it = dd.begin(); it != dd.end(); it++)
  {
    cout << it->first << ": ";
    for(vector<int>::iterator it2 = it->second.begin(); it2 != it->second.end(); it2++)
    {
      cout << *it2 << "  ";
    }
    cout << endl;
  }
}
