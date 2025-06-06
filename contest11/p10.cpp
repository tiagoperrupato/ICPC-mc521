#include <iostream>  
#include <vector>    
#include <tuple>     
#include <limits>    
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;
    
    // To store the original edges
    vector<tuple<int,int,int>> edges;
    edges.reserve(M);

    // Infinity constant for unreachable distances
    const long long INF = numeric_limits<long long>::max() / 4;

    // Initialize distance matrix (1-based indexing)
    vector<vector<long long>> dist(N+1, vector<long long>(N+1, INF));
    for(int i = 1; i <= N; i++){
        dist[i][i] = 0;
    }

    // Read edges and set initial distances
    for(int i = 0; i < M; i++){
        int u, v, w;
        cin >> u >> v >> w;
        edges.emplace_back(u, v, w);
        dist[u][v] = w;
        dist[v][u] = w;
    }

    // Floyd–Warshall all-pairs shortest paths
    for(int k = 1; k <= N; k++){
        for(int i = 1; i <= N; i++){
            if(dist[i][k] == INF) continue;
            for(int j = 1; j <= N; j++){
                long long viaK = dist[i][k] + dist[k][j];
                if(viaK < dist[i][j]){
                    dist[i][j] = viaK;
                }
            }
        }
    }

    // Count edges never on any shortest path
    int answer = 0;
    for(auto &e : edges){
        int u, v, w;
        tie(u, v, w) = e;
        if(dist[u][v] < w){
            answer++;
        }
    }

    cout << answer << "\n";
    return 0;
}
