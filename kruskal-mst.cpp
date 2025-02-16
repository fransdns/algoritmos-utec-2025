#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Graph {
private:
    int V;
    vector<pair<int, pair<int, int>>> edges;

public:
    Graph(int vertices) : V(vertices) {}

    void addEdge(int u, int v, int weight) {
        edges.push_back({weight, {u, v}});
    }

    int findParent(vector<int>& parent, int i) {
        if (parent[i] != i)
            parent[i] = findParent(parent, parent[i]);
        return parent[i];
    }

    void unionSets(vector<int>& parent, vector<int>& rank, int x, int y) {
        int rootX = findParent(parent, x);
        int rootY = findParent(parent, y);
        
        if (rank[rootX] < rank[rootY]) {
            parent[rootX] = rootY;
        } else if (rank[rootX] > rank[rootY]) {
            parent[rootY] = rootX;
        } else {
            parent[rootY] = rootX;
            rank[rootX]++;
        }
    }

    void kruskalMST() {
        sort(edges.begin(), edges.end());
        vector<int> parent(V);
        vector<int> rank(V, 0);
        
        for (int i = 0; i < V; i++) {
            parent[i] = i;
        }
        
        cout << "Aristas del MST:\n";
        for (auto& edge : edges) {
            int weight = edge.first;
            int u = edge.second.first;
            int v = edge.second.second;

            if (findParent(parent, u) != findParent(parent, v)) {
                cout << u << " - " << v << " : " << weight << "\n";
                unionSets(parent, rank, u, v);
            }
        }
    }
};

int main() {
    Graph g(5);
    g.addEdge(0, 1, 2);
    g.addEdge(0, 3, 6);
    g.addEdge(1, 2, 3);
    g.addEdge(1, 3, 8);
    g.addEdge(1, 4, 5);
    g.addEdge(2, 4, 7);
    g.addEdge(3, 4, 9);

    g.kruskalMST();
    
    return 0;
}
