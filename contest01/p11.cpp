#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int sumAP(int n) {
    return n * (n + 1) / 2;
} 

int minOps(int a, int b) {
    int i = 0;
    int absDiff = abs(a - b);
    if (absDiff == 0) {
        return 0;
    } else while(true) {
        if (sumAP(i) >= absDiff && (sumAP(i) - absDiff) % 2 == 0) {
            return i;
        }
        i++;
    }
    return -1;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        int a, b;
        cin >> a >> b;
        cout << minOps(a, b) << endl;
    }
    return 0;
}
