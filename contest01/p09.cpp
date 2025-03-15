#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <utility>
using namespace std;

const int MOD = 998244353;
const int MAXN = 300005;
long long fact[MAXN];

// Pré-computar fatoriais módulo MOD
void precompute_factorial(int n) {
    fact[0] = 1;
    for (int i = 1; i <= n; i++) {
        fact[i] = (fact[i - 1] * i) % MOD;
    }
}

// Função para calcular o número de permutações com elementos repetidos
long long count_repeated_permutations(const vector<int>& values) {
    unordered_map<int, int> freq;
    for (int val : values) freq[val]++;
    
    long long res = 1;
    for (auto [key, count] : freq) {
        res = (res * fact[count]) % MOD;
    }
    return res;
}

// Function to check if a sequence is sorted by a given key
bool is_sorted_by(const vector<pair<int, int>>& seq, int key) {
    for (int i = 1; i < seq.size(); i++) {
        if ((key == 0 && seq[i].first < seq[i - 1].first) ||
            (key == 1 && seq[i].second < seq[i - 1].second)) {
            return false;
        }
    }
    return true;
}

// Função para contar permutações válidas
long long count_good_permutations(int n, vector<pair<int, int>>& pairs) {

    if (n == 1) return 1;
    precompute_factorial(n);
    
    long long total_permutations = fact[n];

    // Ordenar pelo primeiro elemento e calcular permutações repetidas
    vector<int> first_elements(n);
    for (int i = 0; i < n; i++) first_elements[i] = pairs[i].first;
    sort(first_elements.begin(), first_elements.end());
    long long bad_first = count_repeated_permutations(first_elements);

    // Ordenar pelo segundo elemento e calcular permutações repetidas
    vector<int> second_elements(n);
    for (int i = 0; i < n; i++) second_elements[i] = pairs[i].second;
    sort(second_elements.begin(), second_elements.end());
    long long bad_second = count_repeated_permutations(second_elements);

    // Ordenar pelos dois elementos e calcular pares idênticos
    sort(pairs.begin(), pairs.end());
    long long bad_both = 0;
    if (is_sorted_by(pairs, 1)) {
        bad_both = 1;
    
        int count = 1;
        for (int i = 1; i < n; i++) {
            if (pairs[i] == pairs[i - 1]) {
                count++;
            } else {
                bad_both = (bad_both * fact[count]) % MOD;
                count = 1;
            }
        }
        bad_both = (bad_both * fact[count]) % MOD;
    }

    // Aplicar princípio de inclusão-exclusão
    long long good_permutations = (total_permutations - bad_first - bad_second + bad_both) % MOD;
    return good_permutations;
}

int main() {
    int n;
    cin >> n;
    vector<pair<int, int>> pairs(n);
    
    for (int i = 0; i < n; i++) {
        cin >> pairs[i].first >> pairs[i].second;
    }

    cout << count_good_permutations(n, pairs) << '\n';
    return 0;
}