#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

const int INF = numeric_limits<int>::max();

struct Edge {
    int to, weight;
};

void dijkstra(int start, const vector<vector<Edge>>& graph, vector<int>& dist) {
    int n = graph.size();
    dist.assign(n, INF);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    
    dist[start] = 0;
    pq.push({0, start});
    
    while (!pq.empty()) {
        int d = pq.top().first;
        int u = pq.top().second;
        pq.pop();
        
        if (d > dist[u]) continue;
        
        for (const auto& edge : graph[u]) {
            int v = edge.to, weight = edge.weight;
            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }
}

int main() {
    int n, m;
    cout << "Ingrese el número de nodos y aristas: ";
    cin >> n >> m;
    
    vector<vector<Edge>> graph(n);
    cout << "Ingrese las aristas (origen, destino, peso):" << endl;
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].push_back({v, w});
        graph[v].push_back({u, w}); // Si el grafo es dirigido, elimina esta línea
    }
    
    int start;
    cout << "Ingrese el nodo de inicio: ";
    cin >> start;
    
    vector<int> dist;
    dijkstra(start, graph, dist);
    
    cout << "Distancias mínimas desde el nodo " << start << ":\n";
    for (int i = 0; i < n; i++) {
        if (dist[i] == INF) cout << "Nodo " << i << ": INF\n";
        else cout << "Nodo " << i << ": " << dist[i] << "\n";
    }
    
    return 0;
}
