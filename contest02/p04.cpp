#include <iostream>

using namespace std;

int main() {
    
    int n;
    int c;
    cin >> n;
    if (n == 1) {
        c = 1;
        cout << c << endl;
    } else {
        c = 1 + 2 * (n * (n - 1));
        cout << c << endl;
    }
    
    return 0;
}