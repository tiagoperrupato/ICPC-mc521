#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

int S;
string N = "1000000000"; // 10^9 as string
int dp[10][82][2];

int digitDP(int pos, int sum, bool tight) {
    if (sum > S) return 0;
    if (pos == N.size()) return sum == S ? 1 : 0;

    if (dp[pos][sum][tight] != -1) return dp[pos][sum][tight];

    int limit = tight ? (N[pos] - '0') : 9;
    int res = 0;

    for (int d = 0; d <= limit; ++d) {
        res += digitDP(pos + 1, sum + d, tight && (d == limit));
    }

    return dp[pos][sum][tight] = res;
}

int main() {
    cin >> S;
    memset(dp, -1, sizeof(dp));
    cout << digitDP(0, 0, true) << endl;
    return 0;
}