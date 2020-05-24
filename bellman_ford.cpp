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

void initialize_single_source(map<int, map<int, int> > graph, int s, map<int, int> &d, map<int, int> &pi)
{
  for(map<int, map<int, int> >::iterator it = graph.begin(); it != graph.end(); it++){
    d[it->first] = INT_MAX;
    pi[it->first] = INT_MAX;
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

void relax_with_history(int u, int v, int w, map<int, map<int, int> > graph, map<int, vector<int> > &dd, map<int, int> &d, map<int, int> &pi, map<int, int> &q)
{
  relax(u, v, w, graph, d, pi, q);
  /*
  for(map<int, vector<int> >::iterator it = dd.begin(); it != dd.end(); it++)
  {
    for(vector<int>::iterator it2 = it->second.begin(); it2 != it->second.end(); it2++)
    {
      dd.insert(it2->second);
    }
  }
  */
}

bool bellman_ford(map<int, map<int, int> > graph, int s, map<int, vector<int> > &dd)
{
  int u, v, w;
  map<int, int> d, pi;
  initialize_single_source(graph, s, d, pi);
  for(map<int, map<int, int> >::iterator it = graph.begin(); it != graph.end(); it++)
  {
    u = it->first;
    for(map<int, int>::iterator it2 = it->second.begin(); it2 != it->second.end(); it2++)
    {
      v = it2->first;
      w = it2->second;
      cout << u << ", " << v << ", " << w << endl;
      //relax_with_history(u, v, w, graph, dd, d, pi, q);
    }
  }
  return true;
  /*
  //WRONG
  for(map<int, int>::iterator it2 = it->second.begin(); it2 != it->second.end(); it2++)
  {
    if(d[v] > d[u] + INT_MAX)
      return false;
  }
  return true; 
  */
}

void view_bellman_ford_solution(map<int, vector<int> > &dd)
{
  /*
  for(map<int, vector<int> >::iterator it = dd.begin(); it != dd.end(); it++)
  {
    for(vector<int>::iterator it2 = it->second.begin(); it2 != it->second.end(); it2++)
    {
      cout << it2->second;
    }
    cout << endl;
  }
  */
}
