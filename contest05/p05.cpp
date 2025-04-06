#include <iostream>
using namespace std;

int main() {
    int cases;
    cin >> cases;
    for (int i = 0; i < cases; i++) {
        int n, m, k;
        cin >> n >> m >> k;
        int expected_cost = (n - 1) * m + (m - 1);
        if (k == expected_cost) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
    return 0;
}