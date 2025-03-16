#include <iostream>
#include <cmath>
#include <cstdio>
#include <vector>

using namespace std;
typedef vector<int> vi;

void printAdjList(const vector<pair<int, vi>>& AdjList) {
    for (int i = 0; i < AdjList.size(); i++) {
        cout << i + 1 << ": " << AdjList[i].first << ":  ";
        for (int j = 0; j < AdjList[i].second.size(); j++) {
            cout << AdjList[i].second[j] << " ";
        }
        cout << endl;
    }
}

bool isConnectedDFS(const vector<pair<int, vi>>& AdjList, int N, int firstNode, int openNodes) {
    vector<bool> visited(N, false); // Keeps track of visited nodes
    int visitedCount = 0;

    // Helper function for DFS traversal
    function<void(int)> dfs = [&](int u) {
        visited[u] = true;
        visitedCount++;
        for (int v : AdjList[u].second) {
            if (!visited[v - 1]) {
                dfs(v - 1);
            }
        }
    };

    // Start DFS from node firstNode
    dfs(firstNode - 1);

    // If we visited all nodes, the graph is connected
    return visitedCount == openNodes;
}


int main() {
    
    int N, M;
    vector<pair<int, vi>> AdjList;
    vector<int> open;

    cin >> N >> M;
    open.assign(N, 0);
    AdjList.assign(N, pair<int, vi>());

    for (int i = 0; i < N; i++) {
        open[i] = i + 1;
    }

    for (int i = 0; i < M; i++) {
        int u, v;
        cin >> u >> v;
        AdjList[u - 1].second.push_back(v);
        AdjList[v - 1].second.push_back(u);
    }

    for (int i = 0; i < N; i++) {
        if (isConnectedDFS(AdjList, N, open[0], open.size())) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }

        int u;
        cin >> u;

        for (pair<int, vi>& v : AdjList) {
            auto it = find(v.second.begin(), v.second.end(), u);
            if (it != v.second.end())
                v.second.erase(it);
        }
        AdjList[u - 1].second.clear();
        AdjList[u - 1].first = 1;
        open.erase(remove(open.begin(), open.end(), u), open.end());
    }

    return 0;
}