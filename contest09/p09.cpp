#include <iostream>
#include <vector>
#include <queue>
using namespace std;

void bfs(int start, int n, const vector<vector<int>>& adj, vector<int>& dist) {
    fill(dist.begin(), dist.end(), -1);
    queue<int> q;
    q.push(start);
    dist[start] = 0;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : adj[u]) {
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;

    int S, A, B;
    cin >> S >> A >> B;

    vector<vector<int>> adj(N + 1);
    for (int i = 0; i < M; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> d_S(N + 1, -1);
    bfs(S, N, adj, d_S);

    vector<int> d_A(N + 1, -1);
    bfs(A, N, adj, d_A);

    vector<int> d_B(N + 1, -1);
    bfs(B, N, adj, d_B);

    int shortest_A = d_S[A];
    int shortest_B = d_S[B];
    int max_edges = 0;

    for (int X = 1; X <= N; ++X) {
        if (d_S[X] == -1 || d_A[X] == -1 || d_B[X] == -1) {
            continue;
        }
        if (d_S[X] + d_A[X] == shortest_A && d_S[X] + d_B[X] == shortest_B) {
            max_edges = max(max_edges, d_S[X]);
        }
    }

    cout << max_edges << endl;

    return 0;
}