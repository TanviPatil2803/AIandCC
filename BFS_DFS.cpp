#include <iostream>
#include <vector>
#include <list>
#include <queue>
using namespace std;

class Graph {
    int vertices;
    vector<list<int>> adj;

public:
    Graph(int V) : vertices(V), adj(V) {}

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u); // For undirected graph
    }

    void BFS(int start) {
        queue<int> q;
        q.push(start);

        vector<bool> visited(vertices, false);

        visited[start] = true;

        while (!q.empty()) {
            int v = q.front();
            cout << v << " ";
            q.pop();

            for (int u : adj[v]) {
                if (!visited[u]) {
                    q.push(u);
                    visited[u] = true;
                }
            }
        }
    }

    void DFSUtil(int v, vector<bool>& visited) {
        visited[v] = true;
        cout << v << " ";

        for (auto i = adj[v].begin(); i != adj[v].end(); ++i)
            if (!visited[*i])
                DFSUtil(*i, visited);
    }

    void DFS(int v) {
        vector<bool> visited(vertices, false);
        DFSUtil(v, visited);
    }
};

int main() {
    Graph g(8);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(0, 3);
    g.addEdge(1, 0);
    g.addEdge(2, 0);
    g.addEdge(3, 0);
    g.addEdge(1, 4);
    g.addEdge(1, 5);
    g.addEdge(5, 1);
    g.addEdge(4, 1);
    g.addEdge(2, 6);
    g.addEdge(3, 7);
    g.addEdge(6,2);
    g.addEdge(7,3);

    cout << "BFS Traversal starting from node 2: ";
    g.BFS(0);
    cout << endl;

    cout << "DFS Traversal starting from node 2: ";
    g.DFS(0);
    cout << endl;

    return 0;
}
