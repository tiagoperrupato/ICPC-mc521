#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool canSort(vector<vector<int>>& table, int n, int m) {
    // Try all possible column swaps (including no swap)
    for (int c1 = 0; c1 < m; ++c1) {
        for (int c2 = c1; c2 < m; ++c2) {
            // Swap columns c1 and c2
            for (int i = 0; i < n; ++i) {
                swap(table[i][c1], table[i][c2]);
            }

            // Check if each row can be sorted with at most one swap
            bool possible = true;
            for (int i = 0; i < n; ++i) {
                int diff = 0;
                for (int j = 0; j < m; ++j) {
                    if (table[i][j] != j + 1) {
                        ++diff;
                    }
                }
                if (diff > 2) {
                    possible = false;
                    break;
                }
            }

            if (possible) {
                return true;
            }

            // Swap back to original
            for (int i = 0; i < n; ++i) {
                swap(table[i][c1], table[i][c2]);
            }
        }
    }

    return false;
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> table(n, vector<int>(m));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> table[i][j];
        }
    }

    if (canSort(table, n, m)) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }

    return 0;
}