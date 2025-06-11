#include <iostream>
#include <vector>
#include <queue>
#include <utility>

using namespace std;

int mst(int V, vector<vector<pair<int, int>>> &adj) {
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    vector<bool> visited(V, false);
    int res = 0;

    pq.push({0, 0});

    while(!pq.empty()){
        auto [wt, u] = pq.top();
        pq.pop();

        if(visited[u]) continue;

        res += wt;
        visited[u] = true;

        for(auto &[v, w] : adj[u]){
            if(!visited[v]){
                pq.push({w, v});
            }
        }
    }

    return res;
}

int main() {
    int V, E;
    cin >> V >> E;

    vector<vector<pair<int, int>>> adj(V);

    for (int i = 0; i < E; ++i) {
        int u, v, w;
        cin >> u >> v >> w;

        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    cout << mst(V, adj) << endl;

    return 0;
}