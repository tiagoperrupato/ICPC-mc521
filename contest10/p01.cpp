#include <iostream>
#include <vector>

using namespace std;
using ll = long long;
const ll INF = (ll)1e18;

struct Edge {
    int u, v;
    ll w;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int V, E, r;
    cin >> V >> E >> r;

    vector<Edge> edges(E);
    for (int i = 0; i < E; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
    }

    // Initialize distances
    vector<ll> dist(V, INF);
    dist[r] = 0;

    // Relax edges up to V-1 times
    for (int i = 0; i < V - 1; i++) {
        bool updated = false;
        for (const auto &e : edges) {
            if (dist[e.u] < INF && dist[e.v] > dist[e.u] + e.w) {
                dist[e.v] = dist[e.u] + e.w;
                updated = true;
            }
        }
        if (!updated) break;
    }

    // Check for negative-weight cycles
    for (const auto &e : edges) {
        if (dist[e.u] < INF && dist[e.v] > dist[e.u] + e.w) {
            cout << "NEGATIVE CYCLE\n";
            return 0;
        }
    }

    // Output distances
    for (int v = 0; v < V; v++) {
        if (dist[v] == INF) {
            cout << "INF\n";
        } else {
            cout << dist[v] << "\n";
        }
    }

    return 0;
}
