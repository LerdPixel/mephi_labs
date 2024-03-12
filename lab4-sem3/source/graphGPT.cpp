#include <iostream>
#include <list>

using namespace std;

class Graph {
    int V; // Number of vertices

    // Array of lists to store adjacency lists
    list<int> *adj;

public:
    Graph(int V); // Constructor

    // Function to add an edge to the graph
    void addEdge(int v, int w);

    // Function to print the adjacency list representation of the graph
    void printGraph();
};

Graph::Graph(int V) {
    this->V = V;
    adj = new list<int>[V];
}

void Graph::addEdge(int v, int w) {
    adj[v].push_back(w); // Add w to v’s list
    adj[w].push_back(v); // Add v to w’s list
}

void Graph::printGraph() {
    for (int v = 0; v < V; ++v) {
        cout << "Adjacency list of vertex " << v << "\n";
        cout << "head ";
        for (auto x : adj[v])
            cout << "-> " << x;
        cout << "\n";
    }
}

int main() {
    // Create a graph with 5 vertices
    Graph g(5);

    // Add edges
    g.addEdge(0, 1);
    g.addEdge(0, 4);
    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 3);
    g.addEdge(3, 4);

    // Print the adjacency list representation of the graph
    g.printGraph();

    return 0;
}
