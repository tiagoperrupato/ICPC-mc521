#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> A(n), B(n);
    long long sumA = 0, sumB = 0;

    for (int i = 0; i < n; i++) {
        cin >> A[i];
        sumA += A[i];
    }

    for (int i = 0; i < n; i++) {
        cin >> B[i];
        sumB += B[i];
    }

    // Create a vector of (A[i] + B[i], index)
    vector<pair<int, int>> combined;
    for (int i = 0; i < n; i++) {
        combined.push_back({A[i] + B[i], i + 1});
    }

    // Sort in descending order based on the sum of A[i] + B[i]
    sort(combined.rbegin(), combined.rend());

    long long curSumA = 0, curSumB = 0;
    vector<int> indices;

    for (const auto &p : combined) {
        int idx = p.second - 1; // Convert back to 0-based index
        curSumA += A[idx];
        curSumB += B[idx];
        indices.push_back(idx + 1); // Convert to 1-based

        if (2 * curSumA > sumA && 2 * curSumB > sumB) {
            cout << indices.size() << "\n";
            for (int x : indices) {
                cout << x << " ";
            }
            cout << "\n";
            return 0;
        }
    }

    return 0;
}