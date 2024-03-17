#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

const int INF = numeric_limits<int>::max();

// Define a structure for representing edges
struct Edge {
    int to;
    int weight;
    Edge(int t, int w) : to(t), weight(w) {}
};

// Define a structure for representing vertices
struct Vertex {
    int id;
    int distance;
    vector<Edge> edges;
    Vertex(int i) : id(i), distance(INF) {}
};

// Dijkstra's algorithm
vector<int> dijkstra(vector<Vertex>& graph, int start, int end) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    vector<int> prev(graph.size(), -1);

    graph[start].distance = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        int u = pq.top().second;
        int dist = pq.top().first;
        pq.pop();

        if (u == end)
            break;

        if (dist > graph[u].distance)
            continue;

        for (const auto& edge : graph[u].edges) {
            int v = edge.to;
            int alt = graph[u].distance + edge.weight;
            if (alt < graph[v].distance) {
                graph[v].distance = alt;
                prev[v] = u;
                pq.push({alt, v});
            }
        }
    }

    // Reconstruct path
    vector<int> path;
    for (int at = end; at != -1; at = prev[at]) {
        path.push_back(at);
    }
    reverse(path.begin(), path.end());

    return path;
}

int main() {
    // Example usage
    int numVertices = 6;
    vector<Vertex> graph(numVertices, Vertex(-1));

    // Add edges
    graph[0].edges.push_back(Edge(1, 7));
    graph[0].edges.push_back(Edge(2, 9));
    graph[0].edges.push_back(Edge(5, 14));
    graph[1].edges.push_back(Edge(2, 10));
    graph[1].edges.push_back(Edge(3, 15));
    graph[2].edges.push_back(Edge(3, 11));
    graph[2].edges.push_back(Edge(5, 2));
    graph[3].edges.push_back(Edge(4, 6));
    graph[4].edges.push_back(Edge(5, 9));

    // Calculate shortest path from vertex 0 to vertex 4
    vector<int> path = dijkstra(graph, 0, 4);

    // Output shortest path
    cout << "Shortest path from 0 to 4: ";
    for (int node : path) {
        cout << node << " ";
    }
    cout << endl;

    return 0;
}
