#include "dijkstra.h"
#include <iomanip>
using namespace std;

void project_part2(const string &graph_filename, const int s)
{
  map<int, map<int, double> > graph = load_graph(graph_filename);
  map<int, double> d;
  map<int, int> pi;
  dijkstra(graph, s, d, pi);
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
    cout << fixed << showpoint;
    cout << setprecision(1);
    if(C == DBL_MAX)
    {
      cout << " Cost: Infinity.\n";
    }
    else
    {
      cout << " Cost: " << C << ".\n";
    }
  }
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
  project_part2(graph_filename, s); 
  return 0;
}
