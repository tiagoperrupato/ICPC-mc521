#include <iostream>
#include <vector>
#include <bitset>

using namespace std;

const int MOD = 1e9 + 9;

// Check if a number is prime
bool is_prime(int x) {
    if (x < 2) return false;
    for (int d = 2; d * d <= x; ++d)
        if (x % d == 0) return false;
    return true;
}

int main() {
    int n;
    cin >> n;

    // Precompute all 3-digit primes
    bitset<1000> isThreeDigitPrime;
    for (int i = 100; i <= 999; ++i) {
        if (is_prime(i)) isThreeDigitPrime[i] = 1;
    }

    // dp[pos][last2Digits]: number of ways to reach this state
    vector<vector<int>> dp(n + 1, vector<int>(100, 0));

    // Initialize all valid 3-digit primes
    for (int p = 100; p <= 999; ++p) {
        if (isThreeDigitPrime[p]) {
            int last2 = p % 100;
            dp[3][last2] = (dp[3][last2] + 1) % MOD;
        }
    }

    // Build the DP table
    for (int len = 4; len <= n; ++len) {
        for (int last2 = 0; last2 < 100; ++last2) {
            if (dp[len - 1][last2] == 0) continue;
            for (int d = 0; d <= 9; ++d) {
                int new3 = last2 * 10 + d;
                if (isThreeDigitPrime[new3]) {
                    int newLast2 = new3 % 100;
                    dp[len][newLast2] = (dp[len][newLast2] + dp[len - 1][last2]) % MOD;
                }
            }
        }
    }

    // Sum up all valid ways to build n-digit numbers
    int result = 0;
    for (int i = 0; i < 100; ++i) {
        result = (result + dp[n][i]) % MOD;
    }

    cout << result << endl;
    return 0;
}