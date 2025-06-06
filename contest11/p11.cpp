#include <iostream>           
#include <string>            
#include <unordered_map>      
#include <vector>           
#include <cmath>    
#include <limits>  
           
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    int caseNo = 1;

    while ( (cin >> n) && n > 0 ) {
        // 1) Read currency names and assign indices 0..n-1
        unordered_map<string,int> idx;
        string name;
        for (int i = 0; i < n; i++) {
            cin >> name;
            idx[name] = i;
        }

        // 2) Initialize distance matrix for Floyd–Warshall
        const double INF = numeric_limits<double>::infinity();
        vector<vector<double>> dist(n, vector<double>(n, INF));
        for (int i = 0; i < n; i++) {
            dist[i][i] = 0.0;
        }

        // 3) Read exchange rates, store as edge weights = –log(rate)
        cin >> m;
        for (int i = 0; i < m; i++) {
            string u_name, v_name;
            double rate;
            cin >> u_name >> rate >> v_name;
            int u = idx[u_name], v = idx[v_name];
            double w = -log(rate);
            if (w < dist[u][v]) {
                dist[u][v] = w;
            }
        }

        // 4) Floyd–Warshall to find all-pairs shortest paths
        for (int k = 0; k < n; k++) {
            for (int i = 0; i < n; i++) {
                if (dist[i][k] == INF) continue;
                for (int j = 0; j < n; j++) {
                    double via = dist[i][k] + dist[k][j];
                    if (via < dist[i][j]) {
                        dist[i][j] = via;
                    }
                }
            }
        }

        // 5) Check for any negative cycle: dist[i][i] < 0
        bool arbitrage = false;
        for (int i = 0; i < n; i++) {
            if (dist[i][i] < 0.0) {
                arbitrage = true;
                break;
            }
        }

        cout << "Case " << caseNo++
             << ": " << (arbitrage ? "Yes" : "No") << "\n";
    }

    return 0;
}
