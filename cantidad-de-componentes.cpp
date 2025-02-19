#include <iostream>
#include <vector>
using namespace std;

// Estructura para Union-Find (ya implementada)
struct UnionFind {
    vector<int> parent, rank;

    // Constructor
    UnionFind(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; i++)
            parent[i] = i; // Cada nodo es su propio padre al inicio
    }

    // Find con compresión de ruta
    int find(int u) {
        if (u != parent[u])
            parent[u] = find(parent[u]); // Compresión de ruta
        return parent[u];
    }

    // Unión por rango
    void unite(int u, int v) {
        u = find(u), v = find(v);
        if (u == v) return; // Ya están en el mismo conjunto

        // Unir el conjunto más pequeño al más grande
        if (rank[u] > rank[v])
            parent[v] = u;
        else
            parent[u] = v;

        if (rank[u] == rank[v])
            rank[v]++;
    }
};

// Función para contar componentes conectados (¡Tú implementarás esta parte!)
int countComponents(int n, vector<vector<int>>& edges) {
    UnionFind uf(n);

    // Recorre las aristas y une los nodos
    for (const auto& edge : edges) {
        uf.unite(edge[0], edge[1]);
    }

    // Cuenta el número de componentes conectados
    int components = 0;
    for (int i = 0; i < n; i++) {
        if (uf.find(i)==i)
            components++;
    }

    return components;
}

int main() {
    // Ejemplo 1
    int n1 = 5;
    vector<vector<int>> edges1 = {{0, 1}, {1, 2}, {3, 4}};
    cout << "Componentes conectados (Ejemplo 1): " << countComponents(n1, edges1) << endl;

    // Ejemplo 2
    int n2 = 5;
    vector<vector<int>> edges2 = {{0, 1}, {1, 2}, {2, 3}, {3, 4}};
    cout << "Componentes conectados (Ejemplo 2): " << countComponents(n2, edges2) << endl;

    // Ejemplo 2
    int n3 = 5;
    vector<vector<int>> edges3 = {{0, 1},  {3, 4}};
    cout << "Componentes conectados (Ejemplo 3): " << countComponents(n3, edges3) << endl;

    // Ejemplo 2
    int n4 = 5;
    vector<vector<int>> edges4 = {};
    cout << "Componentes conectados (Ejemplo 4): " << countComponents(n4, edges4) << endl;

    return 0;
}
