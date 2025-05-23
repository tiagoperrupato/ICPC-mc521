#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;

    vector<vector<int>> adj(N + 1);
    vector<int> in_degree(N + 1, 0);

    for (int i = 0; i < M; ++i) {
        int X, Y;
        cin >> X >> Y;
        adj[X].push_back(Y);
        in_degree[Y]++;
    }

    queue<int> q;
    for (int i = 1; i <= N; ++i) {
        if (in_degree[i] == 0) {
            q.push(i);
        }
    }

    bool unique_order = true;
    vector<int> order;

    if (q.size() != 1) {
        unique_order = false;
    }

    while (!q.empty() && unique_order) {
        if (q.size() > 1) {
            unique_order = false;
            break;
        }

        int u = q.front();
        q.pop();
        order.push_back(u);

        for (int v : adj[u]) {
            if (--in_degree[v] == 0) {
                q.push(v);
            }
        }

        if (q.size() > 1) {
            unique_order = false;
            break;
        }
    }

    if (unique_order && order.size() == N) {
        vector<int> A(N + 1);
        for (int i = 0; i < N; ++i) {
            A[order[i]] = i + 1;
        }
        cout << "Yes\n";
        for (int i = 1; i <= N; ++i) {
            cout << A[i] << " ";
        }
        cout << "\n";
    } else {
        cout << "No\n";
    }

    return 0;
}