#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

#define INPUT_FILE "closing.in"
#define OUTPUT_FILE "closing.out"

class DSU {
public:
    vector<int> parent, size;

    DSU(int n) {
        parent.resize(n);
        size.resize(n, 1);
        for (int i = 0; i < n; i++) parent[i] = i;
    }

    int find(int x) {
        if (parent[x] == x) return x;
        return parent[x] = find(parent[x]);  // Path compression
    }

    void unite(int x, int y) {
        int rootX = find(x), rootY = find(y);
        if (rootX != rootY) {
            if (size[rootX] < size[rootY]) swap(rootX, rootY);
            parent[rootY] = rootX;
            size[rootX] += size[rootY];
        }
    }
};

int main() {
    ifstream fin(INPUT_FILE);
    ofstream fout(OUTPUT_FILE);

    int N, M;
    fin >> N >> M;

    vector<vector<int>> AdjList(N);
    vector<int> closingOrder(N);
    vector<bool> active(N, false);
    DSU dsu(N);
    
    for (int i = 0; i < M; i++) {
        int u, v;
        fin >> u >> v;
        AdjList[u - 1].push_back(v - 1);
        AdjList[v - 1].push_back(u - 1);
    }

    for (int i = 0; i < N; i++) {
        fin >> closingOrder[i];
        closingOrder[i]--;  // Convert to zero-based index
    }
    fin.close();

    vector<string> result;
    int components = 0;

    // Process barns in reverse closure order (effectively "reopening" them)
    for (int i = N - 1; i >= 0; i--) {
        int barn = closingOrder[i];
        active[barn] = true;
        components++;

        // Connect it to its neighbors if they are also active
        for (int neighbor : AdjList[barn]) {
            if (active[neighbor] && dsu.find(barn) != dsu.find(neighbor)) {
                dsu.unite(barn, neighbor);
                components--;  // Merging reduces the number of components
            }
        }

        // If there's only one component, the farm is fully connected
        result.push_back(components == 1 ? "YES" : "NO");
    }

    // Reverse output order to match original sequence
    for (int i = N - 1; i >= 0; i--) {
        fout << result[i] << endl;
    }

    fout.close();
    return 0;
}