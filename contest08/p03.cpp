#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>
#include <string>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string S;
    if (!getline(cin, S)) return 0;

    // Count frequencies of each lowercase letter
    long long freq[26] = {0};
    for (char c : S) {
        if ('a' <= c && c <= 'z')
            freq[c - 'a']++;
    }

    // Build a min‑heap of all nonzero frequencies
    priority_queue<long long, vector<long long>, greater<long long>> pq;
    for (int i = 0; i < 26; i++) {
        if (freq[i] > 0) {
            pq.push(freq[i]);
        }
    }

    // Special case: if there's only one distinct character,
    // we must still emit 1 bit per symbol.
    if (pq.size() == 1) {
        cout << S.size() << "\n";
        return 0;
    }

    // Greedy Huffman merge: always combine the two smallest weights
    long long totalBits = 0;
    while (pq.size() > 1) {
        long long a = pq.top(); pq.pop();
        long long b = pq.top(); pq.pop();
        long long merged = a + b;
        totalBits += merged;
        pq.push(merged);
    }

    cout << totalBits << "\n";
    return 0;
}
