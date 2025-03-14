#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool canClearField(vector<int>& a) {
    int minHeight = *min_element(a.begin(), a.end());
    
    for (int i = 0; i < a.size(); i++) {
        if ((a[i] - minHeight) % 2 != 0) {
            return false;
        }
    }
    return true;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        cout << (canClearField(a) ? "YES" : "NO") << endl;
    }
    return 0;
}
