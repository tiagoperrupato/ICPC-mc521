#include <iostream>
#include <vector>
#include <set>

using namespace std;

#define MAX_N 100000
// int A[MAX_N], DP[MAX_N];

// int dp_list(int n) {
//     DP[0] = 1;
//     int maxLIS = DP[0];
//     for(int i = 1; i < n; ++i) {
//         DP[i] = 1;

//         for(int j = 0; j < i; ++j) {
            
//             if(A[j] < A[i]) {
//                 DP[i] = max(DP[i], DP[j] + 1);
//             }
//         }
//         maxLIS = max(maxLIS, DP[i]);
//     }
//     return maxLIS;
// }

int lengthOfLIS(vector<int>& nums) {
    vector<int> sub;
    for (int x : nums) {
        if (sub.empty() || sub[sub.size() - 1] < x) {
            sub.push_back(x);
        } else {
            auto it = lower_bound(sub.begin(), sub.end(), x); 
            *it = x; 
        }
    }
    return sub.size();
}

int main() {
    
}

