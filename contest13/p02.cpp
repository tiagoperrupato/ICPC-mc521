#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

const int INF = 1e9;

// Estrutura para representar uma aresta na rede de fluxo
struct Edge {
    int to;       
    int capacity; 
    int rev;     
    bool is_original; 
};

vector<vector<Edge>> adj; 
vector<int> level;     
vector<int> iter;      

// Adiciona uma aresta e sua aresta reversa ao grafo
void add_edge(int u, int v, int cap) {
    adj[u].push_back({v, cap, (int)adj[v].size(), true});
    adj[v].push_back({u, 0, (int)adj[u].size() - 1, false});
}

// Constrói o grafo de níveis com uma BFS
bool bfs(int s, int t) {
    level.assign(adj.size(), -1);
    queue<int> q;
    level[s] = 0;
    q.push(s);
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (const auto& edge : adj[v]) {
            if (edge.capacity > 0 && level[edge.to] < 0) {
                level[edge.to] = level[v] + 1;
                q.push(edge.to);
            }
        }
    }
    return level[t] != -1;
}

// Encontra um fluxo aumentante com uma DFS
int dfs(int v, int t, int f) {
    if (v == t) return f;
    for (int& i = iter[v]; i < (int)adj[v].size(); ++i) {
        Edge& e = adj[v][i];
        if (e.capacity > 0 && level[v] < level[e.to]) {
            int d = dfs(e.to, t, min(f, e.capacity));
            if (d > 0) {
                e.capacity -= d;
                adj[e.to][e.rev].capacity += d;
                return d;
            }
        }
    }
    return 0;
}

// Calcula o fluxo máximo de s para t (Algoritmo de Dinic)
int max_flow(int s, int t) {
    int flow = 0;
    while (bfs(s, t)) {
        iter.assign(adj.size(), 0);
        int f;
        while ((f = dfs(s, t, INF)) > 0) {
            flow += f;
        }
    }
    return flow;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    adj.assign(n + 1, vector<Edge>());

    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        add_edge(u, v, 1);
    }

    int s = 1, t = n;
    int k = max_flow(s, t);

    cout << k << endl;

    // Reconstruir e imprimir os caminhos
    for (int i = 0; i < k; ++i) {
        vector<int> path;
        int cur = s;
        while (cur != t) {
            path.push_back(cur);
            for (auto& edge : adj[cur]) {
                if (edge.is_original && edge.capacity == 0) {
                    edge.is_original = false; 
                    cur = edge.to;
                    break;
                }
            }
        }
        path.push_back(t);

        cout << path.size() << endl;
        for (size_t j = 0; j < path.size(); ++j) {
            cout << path[j] << (j == path.size() - 1 ? "" : " ");
        }
        cout << endl;
    }

    return 0;
}
