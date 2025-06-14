#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Função para resolver um único caso de teste
void solve() {
    int n;
    cin >> n;
    string enemy_pawns_str;
    string gregor_pawns_str;
    cin >> enemy_pawns_str >> gregor_pawns_str;

    vector<bool> target_row_occupied(n, false);

    int successful_pawns = 0;

    for (int i = 0; i < n; ++i) {
        if (gregor_pawns_str[i] == '0') {
            continue;
        }

        // Para cada peão de Gregor, avaliamos as três possíveis jogadas.
        // A ordem de checagem implementa a estratégia gulosa.
        if (enemy_pawns_str[i] == '0' && !target_row_occupied[i]) {
            successful_pawns++;
            target_row_occupied[i] = true;
            continue;
        }

        if (i > 0 && enemy_pawns_str[i - 1] == '1' && !target_row_occupied[i - 1]) {
            successful_pawns++;
            target_row_occupied[i - 1] = true;
            continue; 
        }

        if (i < n - 1 && enemy_pawns_str[i + 1] == '1' && !target_row_occupied[i + 1]) {
        successful_pawns++;
        target_row_occupied[i + 1] = true;
            continue;
        }
    }

    cout << successful_pawns << endl;
}

int main() {
    // Otimização para acelerar a entrada/saída em C++.
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t; // Lê o número de casos de teste.
    while (t--) {
        solve();
    }

    return 0;
}
