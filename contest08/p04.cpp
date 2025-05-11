#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        ll x;
        ll n, m;
        cin >> x >> n >> m;

        // Initialize states for min and max
        ll x_min = x, x_max = x;
        ll F_min = n, C_min = m;
        ll F_max = n, C_max = m;

        // Greedy-step loop: do both min and max in one pass
        while ((x_min > 1 && F_min + C_min > 0) || (x_max > 1 && F_max + C_max > 0)) {
            // Step for minimum
            if (x_min > 1 && F_min + C_min > 0) {
                if (x_min & 1) {  // odd
                    if (F_min > 0) {
                        --F_min;
                        x_min /= 2;
                    } else {
                        --C_min;
                        x_min = (x_min + 1) / 2;
                    }
                } else {          // even
                    if (C_min > 0) {
                        --C_min;
                    } else {
                        --F_min;
                    }
                    x_min /= 2;
                }
            }
            // Step for maximum
            if (x_max > 1 && F_max + C_max > 0) {
                if (x_max & 1) {  // odd
                    if (C_max > 0) {
                        --C_max;
                        x_max = (x_max + 1) / 2;
                    } else {
                        --F_max;
                        x_max /= 2;
                    }
                } else {          // even
                    if (F_max > 0) {
                        --F_max;
                    } else {
                        --C_max;
                    }
                    x_max /= 2;
                }
            }
        }

        // Finalize minimum
        ll mn;
        if (x_min == 0) {
            mn = 0;
        } else if (x_min == 1) {
            mn = (F_min > 0 ? 0 : 1);
        } else {
            // no operations left
            mn = x_min;
        }

        // Finalize maximum
        ll mx;
        if (x_max == 0) {
            mx = 0;
        } else if (x_max == 1) {
            mx = (F_max > 0 ? 0 : 1);
        } else {
            mx = x_max;
        }

        cout << mn << " " << mx;
        if (T) cout << '\n';
    }

    return 0;
}
