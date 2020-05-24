#include "bellman_ford.h"
#include <iomanip>
using namespace std;


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
  map<int, map<int, int> > graph = load_graph(graph_filename);
  map<int, vector<int> > dd;
  if(bellman_ford(graph, s, dd)){
    view_bellman_ford_solution(dd);
  } else {
    cout << "Negative weight cycle detected in graph\n";
  }
  return 0;
}
