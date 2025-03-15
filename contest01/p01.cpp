#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Function to check if we can partition the array into segments with sum `d`
bool canPartition(vector<int>& a, int d, long long S) {
    long long currentSum = 0;
    for (int num : a) {
        currentSum += num;
        if (currentSum == S) {
            return false; // Last segment
        } else if (currentSum == d) {
            currentSum = 0; // Start a new segment
        } else if (currentSum > d) {
            return false; // Exceeded segment sum
        }
    }
    return true; // Ensure all elements are used up correctly
}

// Function to find the maximum possible score
int maxGCDScore(vector<int>& a) {
    int n = a.size();
    long long S = 0;
    for (int num : a) S += num;
    
    long long maxScore = 1;
    
    // Iterate over divisors of S
    for (long long d = 1; d * d <= S; ++d) {
        if (S % d == 0) {
            // Check both divisors d and S/d
            if (canPartition(a, d, S)) maxScore = max(maxScore, d);
            if (canPartition(a, S / d, S)) maxScore = max(maxScore, S / d);
        }
    }
    return maxScore;
}

int main() {
    int t;
    cin >> t;
    
    while (t--) {
        int n;
        cin >> n;
        
        vector<int> a(n);
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
        }
        
        cout << maxGCDScore(a) << "\n";
    }
    
    return 0;
}
