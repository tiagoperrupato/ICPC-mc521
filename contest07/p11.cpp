#include <iostream>
#include <set>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

// Generate all binary decimals up to 100000
vector<int> generate_binary_decimals(int max_val) {
    vector<int> result;
    queue<int> q;
    q.push(1);
    while (!q.empty()) {
        int num = q.front(); q.pop();
        if (num > max_val) continue;
        result.push_back(num);
        q.push(num * 10);
        q.push(num * 10 + 1);
    }
    return result;
}


bool can_be_factored(int x, const vector<int>& binary_decimals) {
    queue<int> q;
    set<int> visited;

    q.push(1);  // Start with 1 (neutral element)
    visited.insert(1);

    while (!q.empty()) {
        int product = q.front(); q.pop();

        for (int b : binary_decimals) {
            if ((long long)product * b > x) continue;
            int new_product = product * b;
            if (new_product == x) return true;
            if (!visited.count(new_product)) {
                visited.insert(new_product);
                q.push(new_product);
            }
        }
    }

    return x == 1;  // Special case
}

int main() {
    int n, x;
    cin >> n;

    vector<int> binary_decimals = generate_binary_decimals(10e5);

    for (int i = 0; i < n; i++) {
        cin >> x;

        cout << (can_be_factored(x, binary_decimals) ? "YES" : "NO") << endl;
    }

    return 0;
}
