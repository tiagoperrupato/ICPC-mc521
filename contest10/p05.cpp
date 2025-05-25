#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <climits>

using namespace std;

typedef long long ll;
const ll INF = LLONG_MAX;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, m, s;
    ll l;
    cin >> n >> m >> s;
    s--;

    vector<vector<pair<int, int>>> adj(n);
    vector<tuple<int, int, int>> roads;
    roads.reserve(m);

    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        u--; v--;
        roads.emplace_back(u, v, w);
        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
    }

    cin >> l;

    vector<ll> dist(n, INF);
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<>> pq;

    dist[s] = 0;
    pq.emplace(0, s);

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (d != dist[u]) continue;
        for (auto [v, w] : adj[u]) {
            if (dist[v] > d + w) {
                dist[v] = d + w;
                pq.emplace(dist[v], v);
            }
        }
    }

    int city_count = 0;
    for (int i = 0; i < n; ++i) {
        if (dist[i] == l) {
            city_count++;
        }
    }

    ll total = city_count;

    for (auto& [u, v, w] : roads) {
        ll du = dist[u];
        ll dv = dist[v];
        ll sum = du + dv + w;

        if (sum == 2 * l) {
            ll x = l - du;
            if (x > 0 && x < w) {
                total++;
            }
        } else {
            ll x1 = l - du;
            if (x1 > 0 && x1 < w && sum >= 2 * l) {
                total++;
            }

            ll x2 = dv + w - l;
            if (x2 > 0 && x2 < w && sum >= 2 * l) {
                total++;
            }
        }
    }

    cout << total << "\n";

    return 0;
}