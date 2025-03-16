#include <iostream>
using namespace std;

bool canMakeMove(int m, int k) {
    if (m <= k) return false;

    if (k == 1) return true;
    
    for (int d = 2; d * d <= m; ++d) {
        if (m % d == 0) {
            // Check both divisors: d and m/d
            if (d >= k || (m / d) >= k) {
                return true;
            }
        }
    }
    return false;
}

int main() {
    int n, m, k;
    cin >> n >> m >> k;
    
    if (!canMakeMove(m, k)) {
        cout << "Marsel" << endl;
    } else if (n % 2 == 1) {
        cout << "Timur" << endl;
    } else {
        cout << "Marsel" << endl;
    }
    
    return 0;
}