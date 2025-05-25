#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
using namespace std;

typedef long long ll;
const ll INF = 1e18;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M, P;
    cin >> N >> M >> P;

    vector<tuple<int, int, int>> edges;
    vector<vector<int>> rev_graph(N + 1);  // Reversed graph for BFS

    for (int i = 0; i < M; ++i) {
        int A, B, C;
        cin >> A >> B >> C;
        edges.emplace_back(A, B, C - P);  // Edge weight is C - P
        rev_graph[B].push_back(A);        // Add reversed edge for BFS
    }

    // BFS to find nodes that can reach N in the original graph
    vector<bool> can_reach_n(N + 1, false);
    queue<int> q;
    q.push(N);
    can_reach_n[N] = true;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : rev_graph[u]) {
            if (!can_reach_n[v]) {
                can_reach_n[v] = true;
                q.push(v);
            }
        }
    }

    // Bellman-Ford algorithm to find maximum possible coins
    vector<ll> dist(N + 1, -INF);
    dist[1] = 0;

    for (int i = 0; i < N - 1; ++i) {
        for (const auto& e : edges) {
            int u = get<0>(e);
            int v = get<1>(e);
            ll w = get<2>(e);
            if (dist[u] != -INF && dist[v] < dist[u] + w) {
                dist[v] = dist[u] + w;
            }
        }
    }

    // Check for possible infinite score (positive cycles)
    bool has_infinite = false;
    for (const auto& e : edges) {
        int u = get<0>(e);
        int v = get<1>(e);
        ll w = get<2>(e);
        if (dist[u] != -INF && dist[v] < dist[u] + w) {
            if (can_reach_n[v]) {
                has_infinite = true;
                break;
            }
        }
    }

    if (has_infinite) {
        cout << -1 << "\n";
    } else {
        ll ans = max(dist[N], 0LL);
        cout << ans << "\n";
    }

    return 0;
}