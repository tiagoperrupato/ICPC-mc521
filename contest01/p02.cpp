#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void sequence_zeros() {
    int n;
    cin >> n;
    vector<int> arr(n);
    
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    
    int max_length = 0, current_length = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] == 0) {
            current_length++;
            max_length = max(max_length, current_length);
        } else {
            current_length = 0;
        }
    }
    
    cout << max_length << std::endl;
}

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        sequence_zeros();
    }
    return 0;
}
