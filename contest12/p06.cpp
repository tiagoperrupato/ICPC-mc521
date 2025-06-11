#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <utility>
using namespace std;

struct DSU {
    vector<int> p;
    DSU(int n): p(n, -1) {}
    int find(int x) {
        return p[x] < 0 ? x : p[x] = find(p[x]);
    }
    bool unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return false;
        if (p[a] > p[b]) swap(a, b);
        p[a] += p[b];
        p[b] = a;
        return true;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<int> U(m), V(m), W(m);
    for (int i = 0; i < m; i++) {
        cin >> U[i] >> V[i] >> W[i];
        --U[i];
        --V[i];
    }

    int q;
    cin >> q;
    vector<bool> ans(q, true);

    int maxW = 0;
    for (int w : W)
        if (w > maxW)
            maxW = w;
    vector<vector<pair<int,int>>> qb(maxW + 1);

    for (int qi = 0; qi < q; qi++) {
        int k;
        cin >> k;
        while (k--) {
            int e;
            cin >> e;
            --e;
            qb[ W[e] ].emplace_back(qi, e);
        }
    }

    vector<int> ord(m);
    iota(ord.begin(), ord.end(), 0);
    sort(ord.begin(), ord.end(),
         [&](int a, int b) { return W[a] < W[b]; });

    vector<int> uniqW;
    uniqW.reserve(m);
    for (int idx : ord) {
        if (uniqW.empty() || W[idx] != uniqW.back()) {
            uniqW.push_back(W[idx]);
        }
    }

    DSU mainDsu(n);
    int ptr = 0;

    for (int w : uniqW) {
        auto &vec = qb[w];
        if (!vec.empty()) {
            sort(vec.begin(), vec.end(),
                 [&](auto &a, auto &b) { return a.first < b.first; });

            int sz = vec.size();
            int i = 0;
            while (i < sz) {
                int qi = vec[i].first;
                if (!ans[qi]) {
                    while (i < sz && vec[i].first == qi) i++;
                    continue;
                }
                int j = i;
                vector<int> nodes;
                while (j < sz && vec[j].first == qi) {
                    int e = vec[j].second;
                    int ru = mainDsu.find(U[e]);
                    int rv = mainDsu.find(V[e]);
                    if (ru == rv) {
                        ans[qi] = false;
                    }
                    nodes.push_back(ru);
                    nodes.push_back(rv);
                    j++;
                }
                if (!ans[qi]) {
                    i = j;
                    continue;
                }
                sort(nodes.begin(), nodes.end());
                nodes.erase(unique(nodes.begin(), nodes.end()), nodes.end());
                int K = nodes.size();
                DSU tempDsu(K);
                auto getId = [&](int x) {
                    return int(lower_bound(nodes.begin(), nodes.end(), x) - nodes.begin());
                };
                for (int t = i; t < j; t++) {
                    int e = vec[t].second;
                    int ru = mainDsu.find(U[e]);
                    int rv = mainDsu.find(V[e]);
                    int iu = getId(ru);
                    int iv = getId(rv);
                    if (!tempDsu.unite(iu, iv)) {
                        ans[qi] = false;
                        break;
                    }
                }
                i = j;
            }
        }
        while (ptr < m && W[ord[ptr]] == w) {
            mainDsu.unite(U[ord[ptr]], V[ord[ptr]]);
            ptr++;
        }
    }

    for (int i = 0; i < q; i++) {
        cout << (ans[i] ? "YES\n" : "NO\n");
    }
    return 0;
}
