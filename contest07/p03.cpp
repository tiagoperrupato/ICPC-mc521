#include <iostream>
#include <vector>
using namespace std;

const int MOD = 1e9 + 7;

int getnCk(int n, int k, vector<vector<int>> &memo) {
  
    // k can not be grater then k so we
  	// return 0 here
    if (k > n)
        return 0;
  
  	// base condition when k and n are 
  	// equal or k = 0
    if (k == 0 || k == n)
        return 1;
	
  	// Check if pair n and k is already 
  	// calculated then return it from here
  	if(memo[n][k] != -1) return memo[n][k];
  
    // Recurvie add the value and store to memorize table
    return memo[n][k] =(getnCk(n - 1, k - 1, memo) 
      					+ getnCk(n - 1, k, memo)) % MOD;
}

int main() {
    vector<vector<int>> memo(500 + 1, vector<int> (500 + 1, -1));
    string s;
    cin >> s;
    int n = s.size();
    vector<vector<int>> dp(n, vector<int>(n, 0));

    // Base case: single character strings
    for (int i = 0; i <= n - 2; i++) {
        if(s[i] == s[i + 1]){
           dp[i][i + 1] = 1;
        }
    }
    for (int i = 1; i <= n - 1; i++) {
        dp[i][i - 1] = 1;
    }

    // Fill the DP table for substrings of increasing length
    for (int len = 3; len <= n; len++) {
        for (int i = 0; (i + len - 1) < n; ++i) {
            int j = i + len - 1;
            dp[i][j] = 0;

            if (len % 2 == 1) {
              continue; // Skip odd lengths
            }
            // Check for all partitions
            for (int k = i; k < j; k++) {
                if (s[k] == s[j]) {
                    // Combine ways to remove parts around this pair
                    if ((k-i) %2 == 0 && (j- i + 1) %2 == 0){
                        int m = (k - i) / 2;
                        int n = (j - i + 1) / 2;
                        dp[i][j] = (dp[i][j] + (dp[i][k - 1] * 1LL * dp[k + 1][j - 1]) % MOD * getnCk(n, m, memo)) % MOD;
                    }
                }
            }
        }
    }

    // Output the result
    cout << dp[0][n - 1] << endl;
    return 0;
}
