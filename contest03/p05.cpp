#include <iostream>
#include <vector>

using namespace std;

int main() {
    cin.sync_with_stdio(0);
    cin.tie(0);

    int len, n;
    cin >> len >> n;
    string seq;
    cin >> seq;

    // Precompute prefix sum array for "AC" occurrences
    vector<int> prefix_AC(len + 1, 0);
    for (int i = 1; i < len; i++) {
        prefix_AC[i + 1] = prefix_AC[i] + (seq[i - 1] == 'A' && seq[i] == 'C');
    }

    // Answer queries in O(1)
    for (int i = 0; i < n; i++) {
        int lower, upper;
        cin >> lower >> upper;
        cout << prefix_AC[upper] - prefix_AC[lower] << "\n";
    }

    return 0;
}