#include <iostream>   // std::cin, std::cout
#include <vector>     // std::vector
#include <limits>     // std::numeric_limits
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int V, E;
    cin >> V >> E;
    // Distance matrix
    const long long INF = numeric_limits<long long>::max() / 4;
    vector<vector<long long>> dist(V, vector<long long>(V, INF));

    // 1) Initialize: zero on the diagonal
    for(int i = 0; i < V; i++){
        dist[i][i] = 0;
    }

    // 2) Read edges
    //    Graph is directed, no parallel edges or self-loops per spec :contentReference[oaicite:0]{index=0}
    for(int i = 0; i < E; i++){
        int s, t;
        long long d;
        cin >> s >> t >> d;
        dist[s][t] = d;
    }

    // 3) Floyd–Warshall: update dist[i][j] via each intermediate k
    for(int k = 0; k < V; k++){
        for(int i = 0; i < V; i++){
            if(dist[i][k] == INF) continue;            // no path i→k
            for(int j = 0; j < V; j++){
                if(dist[k][j] == INF) continue;        // no path k→j
                long long via = dist[i][k] + dist[k][j];
                if(via < dist[i][j]){
                    dist[i][j] = via;
                }
            }
        }
    }

    // 4) Check for negative cycles: any dist[i][i] < 0
    for(int i = 0; i < V; i++){
        if(dist[i][i] < 0){
            cout << "NEGATIVE CYCLE\n";
            return 0;
        }
    }

    // 5) No negative cycle: print the distance matrix
    //    Print "INF" if unreachable, else the numeric cost
    for(int i = 0; i < V; i++){
        for(int j = 0; j < V; j++){
            if(dist[i][j] >= INF/2) {
                cout << "INF";
            } else {
                cout << dist[i][j];
            }
            if(j+1 < V) cout << ' ';
        }
        cout << '\n';
    }

    return 0;
}
