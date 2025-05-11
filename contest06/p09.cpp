#include <iostream>
#include <vector>
using namespace std;

// Memoization table: dp[remaining][maxStep]
vector<vector<int>> dp;

int countWays(int remaining, int maxStep) {
    if (remaining == 0) return 1; // valid partition
    if (remaining < 0 || maxStep == 0) return 0;

    if (dp[remaining][maxStep] != -1) return dp[remaining][maxStep];

    // Two choices:
    // 1. Use step of size maxStep
    int use = countWays(remaining - maxStep, maxStep - 1);

    // 2. Skip step of size maxStep
    int skip = countWays(remaining, maxStep - 1);

    return dp[remaining][maxStep] = use + skip;
}

int main() {
    int N;
    cin >> N;

    // Create DP table initialized with -1
    dp.assign(N + 1, vector<int>(N + 1, -1));

    // Try steps from N-1 down to 1
    int result = countWays(N, N - 1);
    cout << result << endl;

    return 0;
}