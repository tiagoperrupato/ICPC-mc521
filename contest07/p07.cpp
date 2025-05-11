/*
#include <iostream>
#include <vector>
#include <string>

using namespace std;

int countPS(string& s) {
    int n = s.length();
    int res = 0;

    vector<vector<bool>> dp(n, vector<bool>(n, false));
    
    // One length string is always palindrome 
    for (int i = 0; i < n; i++) {
        dp[i][i] = true;
    }

    // Two length string is plaindrome if
    // both characters are same
    for (int i = 0; i < n - 1; i++) {
        if (s[i] == s[i + 1]) {
            dp[i][i + 1] = true;
            res++;
        }
    }

    // Handle palindromes of length 
    // greater than 2 (gap >= 2)
    for (int gap = 2; gap < n; gap++) {
        for (int i = 0; i < n - gap; i++) {
            int j = i + gap;

            // Check if the current string is a palindrome
            if (s[i] == s[j] && dp[i + 1][j - 1]) {
                dp[i][j] = true;
                res++;
            }
        }
    }
  
    return res;

    
}

int main() {
    string s;
    int q;
    cin >> s;
    cin >> q;
    while (q--) {
        int l, r;
        cin >> l >> r;
        string sub = s.substr(l - 1, r - l + 1);
        cout << countPS(sub) + r - l + 1 << endl;
    }
    return 0;
}
*/



#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;
    int n = s.length();

    s = " " + s; // Make the string 1-indexed

    vector<vector<bool>> is_pal(n + 1, vector<bool>(n + 1, false));
    vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));

    // Precompute palindromic substrings
    for (int len = 1; len <= n; ++len) {
        for (int i = 1; i + len - 1 <= n; ++i) {
            int j = i + len - 1;
            if (s[i] == s[j]) {
                if (len <= 2) {
                    is_pal[i][j] = true;
                } else {
                    is_pal[i][j] = is_pal[i + 1][j - 1];
                }
            }
        }
    }

    // Precompute the dp table
    for (int l = n; l >= 1; --l) {
        for (int r = l; r <= n; ++r) {
            if (l + 1 <= n) dp[l][r] += dp[l + 1][r];
            if (r - 1 >= 1) dp[l][r] += dp[l][r - 1];
            if (l + 1 <= n && r - 1 >= 1) dp[l][r] -= dp[l + 1][r - 1];
            if (is_pal[l][r]) dp[l][r]++;
        }
    }

    // Answer queries
    int q;
    cin >> q;
    while (q--) {
        int l, r;
        cin >> l >> r;
        if (l >= 1 && r <= n) {
            cout << dp[l][r] << endl;
        } else {
            cout << "0" << endl; // Handle invalid queries gracefully
        }
    }

    return 0;
}