#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

bool check_sorter(vector<int>& a, int x) {
    vector<int> transformed(a.size());
    for (int i = 0; i < a.size(); i++) {
        transformed[i] = abs(a[i] - x);
    }
    return is_sorted(transformed.begin(), transformed.end());
}

int main() {

    int t;
    cin >> t; // Number of test cases
    while (t--) {
        int n;
        cin >> n; // Length of the array
        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }

        if (is_sorted(a.begin(), a.end())) {
            cout << 0 << endl;
            continue;
        }

        // Find the minimum and maximum values in the array
        int min_val = *min_element(a.begin(), a.end());
        int max_val = *max_element(a.begin(), a.end());
        bool found_num = false;
        
        // Loop from the borders and middle to the center
        int left = min_val;
        int right = max_val;
        int mid_left = (min_val + max_val) / 2;
        int mid_right = mid_left;

        while (left <= mid_left && right >= mid_right) {
            // Check x_left
            if (check_sorter(a, left)) {
                cout << left << endl;
                found_num = true;
                break;
            }

            // Check x_right
            if (check_sorter(a, right)) {
                cout << right << endl;
                found_num = true;
                break;
            }

            // Check mid_left
            if (check_sorter(a, mid_left)) {
                cout << mid_left << endl;
                found_num = true;
                break;
            }

            // Check mid_right
            if (check_sorter(a, mid_right)) {
                cout << mid_right << endl;
                found_num = true;
                break;
            }

            left++;
            right--;
            mid_left--;
            mid_right++;
        }

        if (!found_num) {
            cout << -1 << endl;
        }
    }

    return 0;
}
