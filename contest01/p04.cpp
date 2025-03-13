#include <iostream>
#include <algorithm>
using namespace std;

bool isCorrect(string& s) {
    string standard = "Timur";
    
    string sorted_s = s;
    sort(sorted_s.begin(), sorted_s.end());
    sort(standard.begin(), standard.end());
    
    return sorted_s == standard;
}

int main() {
    int n;
    cin >> n;
    
    while (n--) {
        int length;
        string spelling;
        cin >> length >> spelling;
        if (length != 5) {
            cout << "NO" << endl;
            continue;
        }
        else if (isCorrect(spelling)) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }
    
    return 0;
}