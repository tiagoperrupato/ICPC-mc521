#include <iostream>
using namespace std;

bool test(int n, int m) {
    if (n == m) {
        return true;
    } else if (n % 3 != 0 || n < m) {
        return false;
    }

    return test(n/3, m) || test(2 * n/3, m);
}

int main() {
    int cases, n, m;
    cin >> cases;
    for (int i = 0; i < cases; i++) {
        cin >> n >> m;

        cout << (test(n, m) ? "YES" : "NO") << endl;
    }
    return 0;
}