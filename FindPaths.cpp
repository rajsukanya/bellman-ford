#include "bellman_ford.h"
#include <iomanip>
using namespace std;

void solve_bellman_ford_instance(const string &graph_filename, const int s)
{
  map<int, map<int, int> > graph = load_graph(graph_filename);
  map<int, vector<int> > dd;
  map<int, int> d;
  map<int, int> pi;
  map<int, int> q;
  int w, u, v;
  bellman_ford(graph, w, s, u, v, dd, d, pi, q);
  /*
  for(map<int, map<int, double> >::iterator it = graph.begin(); it != graph.end(); it++){
    vector<int> P; 
    double C;
    int u = it->first;
    dijkstra_traceback(d, pi, s, u, P, C);
    
    cout << u << ": ";
    for(vector<int>::iterator it2 = P.begin(); it2 != P.end(); it2++)
    {
      cout << *it2 << ",";
    }
  }
  */
}

int main(int argc, char **argv)
{
  if(argc != 3)
  {
    cout << "Usage: " << argv[0] << " <graph-file> <vertex> " << endl;
    return 0;
  }
  const string graph_filename(argv[1]);
  const string vertex(argv[2]);
  char *ch = const_cast<char*>(vertex.c_str());
  const int s = atoi(ch);
  solve_bellman_ford_instance(graph_filename, s);
  map<int, vector<int> > dd;
  view_bellman_ford_solution(dd);
  return 0;
}
