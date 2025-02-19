#include <iostream>
#include <vector>
#include <limits>

using namespace std;

const int INF = numeric_limits<int>::max();

struct Edge {
    int from, to, weight;
};

void bellman_ford(int start, int n, const vector<Edge>& edges, vector<int>& dist) {
    dist.assign(n, INF);
    dist[start] = 0;
    
    for (int i = 0; i < n - 1; i++) {
        for (const auto& edge : edges) {
            if (dist[edge.from] != INF && dist[edge.from] + edge.weight < dist[edge.to]) {
                dist[edge.to] = dist[edge.from] + edge.weight;
            }
        }
    }
    
    // Verificación de ciclos negativos
    for (const auto& edge : edges) {
        if (dist[edge.from] != INF && dist[edge.from] + edge.weight < dist[edge.to]) {
            cout << "El grafo contiene un ciclo negativo." << endl;
            return;
        }
    }
}

int main() {
    int n, m;
    cout << "Ingrese el número de nodos y aristas: ";
    cin >> n >> m;
    
    vector<Edge> edges;
    cout << "Ingrese las aristas (origen, destino, peso):" << endl;
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        edges.push_back({u, v, w});
    }
    
    int start;
    cout << "Ingrese el nodo de inicio: ";
    cin >> start;
    
    vector<int> dist;
    bellman_ford(start, n, edges, dist);
    
    cout << "Distancias mínimas desde el nodo " << start << ":\n";
    for (int i = 0; i < n; i++) {
        if (dist[i] == INF) cout << "Nodo " << i << ": INF\n";
        else cout << "Nodo " << i << ": " << dist[i] << "\n";
    }
    
    return 0;
}
