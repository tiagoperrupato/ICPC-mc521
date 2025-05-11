#include <iostream>
#include <vector>

using namespace std;

int main() {
    int N;
    cin >> N;

    if (N == 1) {
        cout << 2 << endl;
        return 0;
    }

    vector<long long> dp(N + 1);
    dp[1] = 2;
    dp[2] = 2;

    for (int i = 3; i <= N; ++i) {
        dp[i] = dp[i-1] + dp[i-2];
    }

    cout << dp[N] << endl;

    return 0;
}