#include <iostream>
#include <vector>
#include <queue>
#include <tuple>

using namespace std;

class Solution {
public:
    vector<int> shortestAlternatingPaths(int n, vector<vector<int>>& redEdges, vector<vector<int>>& blueEdges) {
        vector<vector<pair<int, int>>> adj(n);
        for (auto& edge : redEdges) {
            adj[edge[0]].emplace_back(edge[1], 0); // 0 represents red edge
        }
        for (auto& edge : blueEdges) {
            adj[edge[0]].emplace_back(edge[1], 1); // 1 represents blue edge
        }

        vector<vector<int>> dist(n, vector<int>(2, -1));
        queue<tuple<int, int, int>> q; // (node, color, distance)
        q.emplace(0, 0, 0);
        q.emplace(0, 1, 0);
        dist[0][0] = dist[0][1] = 0;

        while (!q.empty()) {
            auto [node, color, d] = q.front();
            q.pop();
            for (auto& [neighbor, edgeColor] : adj[node]) {
                if (edgeColor != color && dist[neighbor][edgeColor] == -1) {
                    dist[neighbor][edgeColor] = d + 1;
                    q.emplace(neighbor, edgeColor, d + 1);
                }
            }
        }
        
        vector<int> result(n);
        for (int i = 0; i < n; i++) {
            if (dist[i][0] == -1 && dist[i][1] == -1) {
                result[i] = -1;
            } else if (dist[i][0] == -1) {
                result[i] = dist[i][1];
            } else if (dist[i][1] == -1) {
                result[i] = dist[i][0];
            } else {
                result[i] = min(dist[i][0], dist[i][1]);
            }
        }
        return result;
    }
};
