#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

bool compare_recursive(string &a, string &b, int begin_a, int end_a, int begin_b, int end_b) {
    
    if (begin_a == end_a) { // tamanho 1
        return a[begin_a] == b[begin_b];
    }

    if ((end_a - begin_a + 1) % 2 != 0) { // se tamanho ímpar
        return a.substr(begin_a, end_a - begin_a + 1) == b.substr(begin_b, end_b - begin_b + 1);
    }

    int ma = (begin_a + end_a) / 2;
    int mb = (begin_b + end_b) / 2;
    return (compare_recursive(a, b, begin_a, ma, begin_b, mb) && // começo com começo
           compare_recursive(a, b, ma + 1, end_a, mb + 1, end_b)) || // final com final
           (compare_recursive(a, b, begin_a, ma, mb + 1, end_b) && // final com começo
           compare_recursive(a, b, ma + 1, end_a, begin_b, mb)); // começo com final
}

bool compare(string a, string b) {
    if (a == b) {
        return true;
    }
    return compare_recursive(a, b, 0, a.length() - 1, 0, b.length() - 1);
}

int main() {
    string a, b;
    getline(cin, a);
    getline(cin, b);

    cout << (compare(a, b) ? "YES" : "NO") << endl;
    
    return 0;

}