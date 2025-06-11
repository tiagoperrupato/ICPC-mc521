#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdint>

using namespace std;

/*
  Disjoint‐Set (Union–Find) with path compression and union by rank.
*/
struct DSU {
    vector<int> parent, rankv;
    DSU(int n) : parent(n+1), rankv(n+1, 0) {
        for(int i = 1; i <= n; i++) {
            parent[i] = i;
        }
    }
    int find_set(int x) {
        if (parent[x] != x) {
            parent[x] = find_set(parent[x]);
        }
        return parent[x];
    }
    void union_set(int a, int b) {
        a = find_set(a);
        b = find_set(b);
        if (a == b) return;
        if (rankv[a] < rankv[b]) {
            parent[a] = b;
        } else if (rankv[b] < rankv[a]) {
            parent[b] = a;
        } else {
            parent[b] = a;
            rankv[a]++;
        }
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int N, M;
        cin >> N >> M;

        struct Edge {
            int u, v;
            int64_t w;
        };
        vector<Edge> edges;
        edges.reserve(M);

        for (int i = 0; i < M; i++) {
            int A, B;
            int64_t V;
            cin >> A >> B >> V;
            edges.push_back({A, B, V});
        }

        // Sort in descending order by weight:
        sort(edges.begin(), edges.end(),
             [](const Edge &a, const Edge &b) {
                 return a.w > b.w;
             });

        DSU dsu(N);
        int64_t answer = -1;

        for (const auto &e : edges) {
            dsu.union_set(e.u, e.v);
            if (dsu.find_set(1) == dsu.find_set(N)) {
                answer = e.w;
                break;
            }
        }

        cout << answer << "\n";
    }

    return 0;
}
