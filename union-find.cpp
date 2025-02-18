#include <iostream>
#include <vector>
using namespace std;

class UnionFind {
private:
    vector<int> parent;
    vector<int> rank; // También se puede usar "size" para unión por tamaño

public:
    // Constructor: inicializa n conjuntos (cada elemento es su propio padre)
    UnionFind(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }

    // Método find con compresión de caminos (path compression)
    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]); // Path compression
        }
        return parent[x];
    }

    // Método union: une dos conjuntos usando unión por rango (union by rank)
    void unionSets(int x, int y) {
        int xroot = find(x);
        int yroot = find(y);
        if (xroot == yroot) return; // Ya están en el mismo conjunto

        // Unión por rango
        if (rank[xroot] < rank[yroot]) {
            parent[xroot] = yroot;
        } else if (rank[xroot] > rank[yroot]) {
            parent[yroot] = xroot;
        } else {
            parent[yroot] = xroot;
            rank[xroot]++;
        }
    }
};

int main() {
    int n = 10; // Ejemplo con 10 elementos
    UnionFind uf(n);

    // Unimos algunos elementos
    uf.unionSets(2, 3);
    uf.unionSets(3, 4);
    uf.unionSets(5, 6);
    uf.unionSets(7, 8);

    // Verificamos si 2 y 4 están en el mismo conjunto
    if (uf.find(2) == uf.find(4)) {
        cout << "2 y 4 están en el mismo conjunto" << endl;
    } else {
        cout << "2 y 4 están en diferentes conjuntos" << endl;
    }

    // Verificamos si 2 y 5 están en el mismo conjunto
    if (uf.find(2) == uf.find(5)) {
        cout << "2 y 5 están en el mismo conjunto" << endl;
    } else {
        cout << "2 y 5 están en diferentes conjuntos" << endl;
    }

    return 0;
}
