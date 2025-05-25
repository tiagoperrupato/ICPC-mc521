#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;
using ll = long long;
static constexpr ll   NEG_INF = numeric_limits<ll>::min();

struct Edge {
    int u, v;
    ll w;
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;

    vector<Edge> edges;
    edges.reserve(M);

    // adjacency list for reverse graph to check reachability to N
    vector<vector<int>> rev_adj(N+1);

    for(int i = 0; i < M; i++){
        int a, b;
        ll c;
        cin >> a >> b >> c;
        edges.push_back({a, b, c});
        rev_adj[b].push_back(a);
    }

    // 1) Find which vertices can reach N (in the original graph)
    vector<bool> canReachN(N+1, false);
    queue<int> q;
    canReachN[N] = true;
    q.push(N);
    while(!q.empty()){
        int v = q.front(); q.pop();
        for(int u : rev_adj[v]){
            if(!canReachN[u]){
                canReachN[u] = true;
                q.push(u);
            }
        }
    }

    // 2) Longest‐path Bellman–Ford from source = 1
    vector<ll> dist(N+1, NEG_INF);
    dist[1] = 0;

    // Relax edges N-1 times
    for(int iter = 0; iter < N-1; iter++){
        bool any = false;
        for(auto &e : edges){
            if(dist[e.u] != NEG_INF && dist[e.u] + e.w > dist[e.v]){
                dist[e.v] = dist[e.u] + e.w;
                any = true;
            }
        }
        if(!any) break;
    }

    // 3) Check for a positive-weight cycle that can still reach N
    for(auto &e : edges){
        if(dist[e.u] != NEG_INF
           && dist[e.u] + e.w > dist[e.v]
           && canReachN[e.v])
        {
            cout << "inf\n";
            return 0;
        }
    }

    // 4) Otherwise answer is dist[N]
    //    (problem guarantees N is reachable from 1 in the input)
    cout << dist[N] << "\n";
    return 0;
}
