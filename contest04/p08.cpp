#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int N, H, X;
    cin >> N >> H >> X;
    std::vector<int> P(N);
    for (int i = 0; i < N; ++i) {
        cin >> P[i];
    }

    cout << lower_bound(P.begin(), P.end(), X - H) - P.begin() + 1 << endl;
    return 0;

}