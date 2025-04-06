#include <iostream>
#include <vector>
#include <map>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        if (a[i] > 0) a[i] = 1;
        else a[i] = -1;
    }
    
    long long neg = 0, pos = 0;
    int total_neg = 0; // counts the number of negative prefixes up to current point
    int prefix = 1;
    map<int, int> count; // count of prefix sign occurrences
    count[prefix] = 1;
    
    for (int i = 0; i < n; ++i) {
        prefix *= a[i];
        if (prefix == 1) {
            pos += count[1];
            neg += count[-1];
        } else {
            pos += count[-1];
            neg += count[1];
        }
        count[prefix]++;
    }
    
    cout << neg << " " << pos << "\n";
    return 0;
}