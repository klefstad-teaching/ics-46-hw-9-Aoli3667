#include "dijkstras.h"
#include <queue>
#include <vector>

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous)
{
    int n = G.size();
    vector<bool> visited(n, false);
    vector<int> distance(n, INF);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;

    previous.assign(n, -1); 
    distance[source] = 0;
    pq.push({0, source});

    while (!pq.empty()) 
    {
        //int dist = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (visited[u]) continue;
        visited[u] = true;

        for (const Edge& edge : G[u]) 
        {
            int v = edge.dst;
            int weight = edge.weight; 
            if (!visited[v] && distance[u] + weight < distance[v]) 
            {
                distance[v] = distance[u] + weight;
                previous[v] = u; 
                pq.push({distance[v], v});
            }
        }
    }
    return distance;
}


vector<int> extract_shortest_path(const vector<int>& distances, const vector<int>& previous, int destination)
{
    vector<int> path;
    if (distances[destination] == INF) return path;

    for (int at = destination; at != -1; at = previous[at]) 
    {
        path.push_back(at);
    }
    return path;
}

void print_path(const vector<int>& v, int total)
{
    for(int i = 0; i < v.size(); i++)
    {
        cout << v[i] << " ";
    }
    /*
    for (int i = (int)v.size() - 1; i >= 0; i--) 
    {
        cout << v[i] << " ";
    }
    */
    cout << endl;
    cout << "Total cost is " << total << endl;
}