#include <iostream>
#include <vector>

using namespace std;

vector<long long> len;

char getChar(int n, long long k) {
    if (n == 0) return 'a';
    if (n == 1) return 'b';
    if (n == 2) return 'c';

    if (k <= len[n - 1]) {
        return getChar(n - 1, k);
    } else if (k <= len[n - 1] + len[n - 2]) {
        return getChar(n - 2, k - len[n - 1]);
    } else {
        return getChar(n - 3, k - len[n - 1] - len[n - 2]);
    }
}

int main() {
    int N;
    long long K;
    cin >> N >> K;

    len.resize(N + 1);
    len[0] = 1;
    len[1] = 1;
    len[2] = 1;

    for (int i = 3; i <= N; ++i) {
        len[i] = len[i - 1] + len[i - 2] + len[i - 3];
        if (len[i] > K) len[i] = K + 1;  // evita overflow
    }

    if (K > len[N]) {
        cout << -1 << endl;
    } else {
        cout << getChar(N, K) << endl;
    }

    return 0;
}