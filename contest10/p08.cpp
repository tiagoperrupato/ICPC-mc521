#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;
using ll = long long;
static constexpr ll INF = numeric_limits<ll>::max();

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int V, E, r;
    cin >> V >> E >> r;

    // Build adjacency list: for each u, store (v, w)
    vector<vector<pair<int,int>>> adj(V);
    for (int i = 0; i < E; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].emplace_back(v, w);
    }

    // dist[v] = current best known distance from r to v
    vector<ll> dist(V, INF);
    dist[r] = 0;

    // Min-heap of (distance, vertex)
    priority_queue<pair<ll,int>, vector<pair<ll,int>>, greater<>> pq;
    pq.emplace(0, r);

    while (!pq.empty()) {
        auto [d, u] = pq.top(); 
        pq.pop();
        // If we've already found a better way, skip
        if (d > dist[u]) continue;

        // Relax all edges out of u
        for (auto &[v, w] : adj[u]) {
            ll nd = d + w;
            if (nd < dist[v]) {
                dist[v] = nd;
                pq.emplace(nd, v);
            }
        }
    }

    // Output results
    for (int v = 0; v < V; v++) {
        if (dist[v] == INF) 
            cout << "INF\n";
        else 
            cout << dist[v] << "\n";
    }

    return 0;
}
