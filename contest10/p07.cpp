#include <iostream>
#include <vector>
#include <queue>
using namespace std;

void solve() {
    int n;
    cin >> n;
    string row0, row1;
    cin >> row0 >> row1;
    
    vector<vector<bool>> visited(2, vector<bool>(n, false));
    queue<pair<int, int>> q;
    q.emplace(0, 0);
    visited[0][0] = true;
    
    const int dr[] = {-1, 1, 0, 0};
    const int dc[] = {0, 0, -1, 1};
    const int target_r = 1, target_c = n - 1;
    
    bool found = false;
    while (!q.empty() && !found) {
        auto [r, c] = q.front();
        q.pop();
        
        for (int i = 0; i < 4; ++i) {
            int nr = r + dr[i];
            int nc = c + dc[i];
            
            if (nr < 0 || nr >= 2 || nc < 0 || nc >= n) continue;
            
            char arrow = (nr == 0) ? row0[nc] : row1[nc];
            int nc2 = (arrow == '>') ? nc + 1 : nc - 1;
            
            if (nr == target_r && nc2 == target_c) {
                found = true;
                break;
            }
            
            if (!visited[nr][nc2]) {
                visited[nr][nc2] = true;
                q.emplace(nr, nc2);
            }
        }
        if (found) break;
    }
    
    cout << (found ? "YES" : "NO") << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    
    return 0;
}