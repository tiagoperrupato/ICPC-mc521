#include <iostream>

using namespace std;


int main() {
    int t, n;
    cin >> t;
    while (t--) {
        cin >> n;
        int a[n];
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        
        int num = 0;
        int idx = -1;
        bool sol = false;
        for (int i = 0; i < n; i++) {

            if (a[i] % 2 == 0) {
                num = 1;
                idx = i;
                sol = true;
                cout << num << endl << idx + 1 << endl;
                break;
            } else {
                num++;
                if (num == 2) {
                    cout << num << endl << idx + 1 << " " << i + 1 << endl;
                    sol = true;
                    break;
                }
                idx = i;
            }
        }
        if (!sol) {
            cout << -1 << endl;
        }
    }
    return 0;
}