#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

bool is_extended_recursive(string &s, int begin, int end, char reference, int left) {
    if (begin == end) {
        if (left) {
            return s[begin] <= reference;
        } else {
            return s[begin] >= reference;
        }
    }
        
    int m = (begin + end) / 2;
    char middlechar = s[m];

    if (left) {
        return middlechar <= reference && is_extended_recursive(s, begin, m, middlechar, 1) && is_extended_recursive(s, m + 1, end, middlechar, 0);
    } else {
        return middlechar >= reference && is_extended_recursive(s, begin, m, middlechar, 1) && is_extended_recursive(s, m + 1, end, middlechar, 0);
    }
}

bool is_extended(string s) {
    int m = s.length() / 2;
    return s.length() == 0 || (is_extended_recursive(s, 0, m, s[m], 1) && is_extended_recursive(s, m, s.length() - 1, s[m], 0));
}

int main() {
    string s;
    getline(cin, s);
    cout << (is_extended(s) ? "Yes" : "No") << endl;
    
    return 0;
}