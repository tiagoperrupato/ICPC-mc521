#include <iostream>
#include <vector>
#include <queue>
#include <string>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<string> grid(n);
    for (int i = 0; i < n; i++) {
        cin >> grid[i];
    }

    vector<vector<bool>> vis(n, vector<bool>(m, false));
    int rooms = 0;

    // Directions: up, right, down, left
    const int dr[4] = {-1, 0, 1,  0};
    const int dc[4] = { 0, 1, 0, -1};

    // BFS from (r,c)
    auto bfs = [&](int sr, int sc) {
        queue<pair<int,int>> q;
        q.emplace(sr, sc);
        vis[sr][sc] = true;
        while (!q.empty()) {
            auto [r, c] = q.front(); q.pop();
            for (int d = 0; d < 4; d++) {
                int nr = r + dr[d];
                int nc = c + dc[d];
                if (nr >= 0 && nr < n && nc >= 0 && nc < m
                    && !vis[nr][nc] && grid[nr][nc] == '.') {
                    vis[nr][nc] = true;
                    q.emplace(nr, nc);
                }
            }
        }
    };

    // Iterate all cells; start a BFS whenever we find an unvisited floor cell
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == '.' && !vis[i][j]) {
                rooms++;
                bfs(i, j);
            }
        }
    }

    cout << rooms << "\n";
    return 0;
}
