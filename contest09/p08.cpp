#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<vector<int>> adj(n + 1);
    vector<int> degree(n + 1, 0);

    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
        degree[a]++;
        degree[b]++;
    }

    vector<bool> visited(n + 1, false);
    bool is_reasonable = true;

    for (int i = 1; i <= n; ++i) {
        if (!visited[i]) {
            queue<int> q;
            q.push(i);
            visited[i] = true;
            vector<int> component;

            while (!q.empty()) {
                int u = q.front();
                q.pop();
                component.push_back(u);

                for (int v : adj[u]) {
                    if (!visited[v]) {
                        visited[v] = true;
                        q.push(v);
                    }
                }
            }

            int k = component.size();
            int required_degree = k - 1;
            for (int u : component) {
                if (degree[u] != required_degree) {
                    is_reasonable = false;
                    break;
                }
            }
            if (!is_reasonable) break;
        }
    }

    cout << (is_reasonable ? "YES" : "NO") << endl;

    return 0;
}