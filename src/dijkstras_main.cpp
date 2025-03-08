#include "dijkstras.h"

int main()
{
    Graph G;
    file_to_graph("small.txt", G);
    vector<int> previous;
    vector<int> distances = dijkstra_shortest_path(G, 0, previous);
    vector<int> path = extract_shortest_path(distances, previous, 2);
    //print_path(path, distances[3]);
    print_path(path, distances[2]);
}