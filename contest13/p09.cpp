#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

#ifdef _MSC_VER
#include <intrin.h>
#define __builtin_popcount __popcnt
#endif

using namespace std;

const int INF = 1e9;

void solve(int n) {

    vector<int> baby_cols(n);
    vector<int> valid_cols(n);

    // Lê as posições das rainhas do bebê.
    for (int i = 0; i < n; ++i) {
        std::cin >> baby_cols[i];
    }
    // Lê as posições das rainhas da solução válida.
    for (int i = 0; i < n; ++i) {
        cin >> valid_cols[i];
    }

    // Tabela de DP. O tamanho é 2^n para cobrir todas as máscaras de bits possíveis.
    vector<int> dp(1 << n, INF);
    dp[0] = 0;

    // Itera por todas as máscaras de bits possíveis.
    for (int mask = 1; mask < (1 << n); ++mask) {
        int k = __builtin_popcount(mask);

        for (int j = 1; j <= n; ++j) {
            if ((mask >> (j - 1)) & 1) {
                int prev_mask = mask ^ (1 << (j - 1));

                int cost = abs(k - j) + abs(baby_cols[k - 1] - valid_cols[j - 1]);
                
                if (dp[prev_mask] != INF) {
                    dp[mask] = min(dp[mask], dp[prev_mask] + cost);
                }
            }
        }
    }
    
    cout << dp[(1 << n) - 1] << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    while (cin >> n && n != 0) {
        solve(n);
    }

    return 0;
}
