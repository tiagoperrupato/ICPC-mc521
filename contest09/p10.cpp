#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 200005;
vector<int> tree[MAXN];
int subordinates[MAXN];

// DFS function to count subordinates
int dfs(int node) {
    int count = 0;
    for (int child : tree[node]) {
        count += 1 + dfs(child); // count child and its subordinates
    }
    subordinates[node] = count;
    return count;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    // Build the tree
    for (int i = 2; i <= n; ++i) {
        int boss;
        cin >> boss;
        tree[boss].push_back(i);
    }

    // Run DFS from the general director (node 1)
    dfs(1);

    // Output the number of subordinates for each employee
    for (int i = 1; i <= n; ++i) {
        cout << subordinates[i] << " ";
    }
    cout << "\n";

    return 0;
}
