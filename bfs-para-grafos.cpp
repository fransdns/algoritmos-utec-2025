#include <iostream>
#include <vector>
#include <queue>

using namespace std;

void bfs(int start, int n, vector<vector<int>>& adj) {
    vector<bool> visited(n, false);
    queue<int> q;
    
    visited[start] = true;
    q.push(start);
    
    cout << "Recorrido BFS desde el nodo " << start << ": ";
    
    while (!q.empty()) {
        int node = q.front();
        q.pop();
        cout << node << " ";
        
        for (int neighbor : adj[node]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }
    cout << endl;
}

int main() {
    int n, m;
    cout << "Ingrese el número de nodos y aristas: ";
    cin >> n >> m;
    
    vector<vector<int>> adj(n);
    cout << "Ingrese las aristas (origen, destino):" << endl;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u); // Para grafo no dirigido
    }
    
    int start;
    cout << "Ingrese el nodo de inicio: ";
    cin >> start;
    
    bfs(start, n, adj);
    
    return 0;
}
