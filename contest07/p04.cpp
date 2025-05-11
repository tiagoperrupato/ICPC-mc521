#include <iostream>
#include <vector>

// Para acelerar input/output
std::ios_base::sync_with_stdio(false);
std::cin.tie(nullptr);

int f(int k, const std::vector<int>& A, int l, int r) {
    int ans = 0;

    for (int i = l - 1; i < r; ++i) {
        while (k % A[i] == 0) {
            k /= A[i];
        }
        ans += k;
    }

    return ans;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int testcases;
    std::cin >> testcases;

    while (testcases--) {
        int n, q;
        std::cin >> n >> q;

        std::vector<int> A(n);
        for (int i = 0; i < n; ++i) {
            std::cin >> A[i];
        }

        for (int query = 0; query < q; ++query) {
            int k, l, r;
            std::cin >> k >> l >> r;
            std::cout << f(k, A, l, r) << '\n';
        }
    }

    return 0;
}
