#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int knapSack(int W, vector<int> &val, vector<int> &wt, vector<int> &maxItem) {
    vector<int> dp(W + 1, 0);

    vector<int> new_val, new_wt;
    for (int i = 0; i < val.size(); i++) {
        int count = maxItem[i];
        int k = 1;
        while (count > 0) {
            int use = min(k, count);
            new_val.push_back(val[i] * use);
            new_wt.push_back(wt[i] * use);
            count -= use;
            k *= 2;
        }
    }

    for (int i = 0; i < new_val.size(); i++) {
        for (int j = W; j >= new_wt[i]; j--) {
            dp[j] = max(dp[j], dp[j - new_wt[i]] + new_val[i]);
        }
    }

    return dp[W];
}

int main() {
    int N, W;
    vector<int> val, wt, maxItem;

    cin >> N >> W;
    for(int i = 0; i < N; i++) {
        int v, w, m;
        cin >> v >> w >> m;
        val.push_back(v);
        wt.push_back(w);
        maxItem.push_back(m);
    }
    // Call the knapSack function
    cout << knapSack(W, val, wt, maxItem) << endl;
}
