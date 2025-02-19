#include <iostream>
#include <vector>
#include <limits>

using namespace std;

struct Edge {
    int u, v, weight;
};

void bellmanFord(int n, int start, vector<Edge>& edges) {
    vector<int> dist(n, numeric_limits<int>::max());
    dist[start] = 0;

    // Relajar todas las aristas (n - 1) veces
    for (int i = 0; i < n - 1; i++) {
        for (const auto& edge : edges) {
            if (dist[edge.u] != numeric_limits<int>::max() && 
                dist[edge.u] + edge.weight < dist[edge.v]) {
                dist[edge.v] = dist[edge.u] + edge.weight;
            }
        }
    }

    // **Verificar ciclos negativos**
    for (const auto& edge : edges) {
        if (dist[edge.u] != numeric_limits<int>::max() && 
            dist[edge.u] + edge.weight < dist[edge.v]) {
            cout << "Se ha detectado un ciclo negativo en el grafo.\n";
            return;
        }
    }

    // Imprimir las distancias mínimas
    cout << "Distancias desde el nodo " << start << ":\n";
    for (int i = 0; i < n; i++) {
        cout << "Nodo " << i << ": " << (dist[i] == numeric_limits<int>::max() ? "INF" : to_string(dist[i])) << "\n";
    }
}

int main() {
    int n = 5; // Número de nodos
    vector<Edge> edges = {
        {0, 1, 6}, {0, 2, 7}, {1, 2, 8},
        {1, 3, 5}, {1, 4, -4}, {2, 3, -3},
        {2, 4, 9}, {3, 1, -2}, {4, 3, 7}
    };

    bellmanFord(n, 0, edges);
    return 0;
}