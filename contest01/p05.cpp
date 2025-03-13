#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    
    int t;
    cin >> t;

    while (t--) {
        int n;
        int a;
        int sum = 0;
        int cmp;
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> a;
            sum += a;
        }
        cmp = sum - n;
        if (cmp < 0) {
            a = 1;
        } else if (cmp == 0) {
            a = 0;
        } else {
            a = cmp;
        }
        cout << a << endl;
    }

    return 0;
}