#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>

using namespace std;
static const long long INF = numeric_limits<long long>::max();

struct Edge {
    int u, v;
    long long w;
};

long long edmonds(int n, int root, const vector<Edge>& edges_orig) {
    long long total_cost = 0;
    int r = root;
    vector<Edge> edges = edges_orig;

    while (true) {
        vector<long long> in_cost(n, INF);
        vector<int> pre(n, -1);

        for (auto &e : edges) {
            if (e.u != e.v && e.w < in_cost[e.v]) {
                in_cost[e.v] = e.w;
                pre[e.v] = e.u;
            }
        }
        in_cost[r] = 0;

        for (int v = 0; v < n; v++) {
            if (v == r) continue;
            if (in_cost[v] == INF) return -1;
        }

        for (int v = 0; v < n; v++) {
            total_cost += in_cost[v];
        }

        vector<int> id(n, -1), vis(n, -1);
        int cnt_contract = 0;

        for (int v = 0; v < n; v++) {
            if (v == r || id[v] != -1) continue;
            int cur = v;
            while (vis[cur] != v && id[cur] == -1 && cur != r) {
                vis[cur] = v;
                cur = pre[cur];
            }
            if (cur == r || id[cur] != -1) continue;
            for (int x = pre[cur]; x != cur; x = pre[x]) {
                id[x] = cnt_contract;
            }
            id[cur] = cnt_contract++;
        }

        if (cnt_contract == 0) break;

        for (int v = 0; v < n; v++) {
            if (id[v] == -1) id[v] = cnt_contract++;
        }

        vector<Edge> new_edges;
        new_edges.reserve(edges.size());
        for (auto &e : edges) {
            int u_id = id[e.u], v_id = id[e.v];
            if (u_id != v_id) {
                new_edges.push_back({u_id, v_id, e.w - in_cost[e.v]});
            }
        }

        n = cnt_contract;
        r = id[r];
        edges.swap(new_edges);
    }

    return total_cost;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<long long> q(n);
    for (int i = 0; i < n; i++) {
        cin >> q[i];
    }

    long long maxq = -1;
    for (auto &x : q) {
        maxq = max(maxq, x);
    }

    int root_count = 0, root_index = -1;
    for (int i = 0; i < n; i++) {
        if (q[i] == maxq) {
            root_count++;
            root_index = i;
        }
    }
    if (root_count != 1) {
        cout << -1 << "\n";
        return 0;
    }

    int m;
    cin >> m;
    vector<Edge> edges;
    edges.reserve(m);
    vector<vector<int>> adj(n);
    for (int i = 0; i < m; i++) {
        int a, b;
        long long c;
        cin >> a >> b >> c;
        --a; --b;
        edges.push_back({a, b, c});
        adj[a].push_back(b);
    }

    vector<bool> seen(n, false);
    vector<int> stack = {root_index};
    seen[root_index] = true;
    while (!stack.empty()) {
        int u = stack.back();
        stack.pop_back();
        for (int v : adj[u]) {
            if (!seen[v]) {
                seen[v] = true;
                stack.push_back(v);
            }
        }
    }
    for (int i = 0; i < n; i++) {
        if (!seen[i]) {
            cout << -1 << "\n";
            return 0;
        }
    }

    long long answer = edmonds(n, root_index, edges);
    cout << answer << "\n";
    return 0;
}
