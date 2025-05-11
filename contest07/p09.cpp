#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, t;
    cin >> t;
    while(t--) {
        cin >> n;

        // Crivo de Eratóstenes para achar todos os primos até n
        vector<bool> is_prime(n + 1, true);
        is_prime[0] = is_prime[1] = false;
        for (int i = 2; i * i <= n; ++i) {
            if (is_prime[i]) {
                for (int j = i * i; j <= n; j += i)
                    is_prime[j] = false;
            }
        }

        // Conta os pares (g, g*p) onde p é primo e g*p <= n
        int count = 0;
        for (int p = 2; p <= n; ++p) {
            if (!is_prime[p]) continue;
            for (int g = 1; g * p <= n; ++g) {
                count++;
            }
        }

        cout << count << endl;
    }
    return 0;
}