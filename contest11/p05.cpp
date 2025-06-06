#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric> // for std::iota (not strictly needed here but good for index ops)

// Function to check if a string is sorted
bool is_string_sorted(const std::string& s) {
    for (size_t i = 0; i + 1 < s.length(); ++i) {
        if (s[i] > s[i + 1]) {
            return false;
        }
    }
    return true;
}

// Function to find the lexicographically largest subsequence (LLS)
// Returns a pair: vector of characters in LLS, vector of original indices
std::pair<std::vector<char>, std::vector<int>> find_lls(const std::string& s) {
    int n = s.length();
    if (n == 0) {
        return {{}, {}};
    }

    // suffix_max_char[i] stores the maximum character in s[i...n-1]
    std::vector<char> suffix_max_char(n);
    suffix_max_char[n - 1] = s[n - 1];
    for (int i = n - 2; i >= 0; --i) {
        suffix_max_char[i] = std::max(s[i], suffix_max_char[i + 1]);
    }

    std::vector<char> lls_chars_values; // Stores the characters s[index] for LLS
    std::vector<int> lls_indices_list;
    int current_s_idx = 0;
    while (current_s_idx < n) {
        char char_to_pick = suffix_max_char[current_s_idx];
        int k = -1; // Will store the index of char_to_pick
        // Find the first occurrence of char_to_pick starting from current_s_idx
        for (int i = current_s_idx; i < n; ++i) {
            if (s[i] == char_to_pick) {
                k = i;
                break;
            }
        }
        
        // This check is more for robustness; k should always be found if logic is correct
        if (k == -1) { 
            break; 
        }
        
        lls_chars_values.push_back(s[k]);
        lls_indices_list.push_back(k);
        current_s_idx = k + 1;
    }
    return {lls_chars_values, lls_indices_list};
}


void solve_test_case() {
    int n;
    std::cin >> n;
    std::string s_current;
    std::cin >> s_current;

    // Initial check for already sorted string
    if (is_string_sorted(s_current)) {
        std::cout << 0 << std::endl;
        return;
    }

    // Max iterations to prevent TLE.
    // Based on typical contest problem patterns and sum N constraints.
    // If N is small (e.g., up to ~200), N-1 operations might occur.
    // For larger N, K must be small. A cap around 205 covers N-1 for N up to 200.
    const int MAX_OPERATIONS_LIMIT = 205; 

    for (int ops_performed = 1; ops_performed <= MAX_OPERATIONS_LIMIT; ++ops_performed) {
        std::string s_before_op = s_current;

        auto lls_result = find_lls(s_current);
        std::vector<char> lls_chars = lls_result.first; // These are t1, t2, ..., tm
        std::vector<int> lls_indices = lls_result.second;

        // This should not happen if s_current is non-empty and find_lls is correct.
        if (lls_chars.empty()) { 
            std::cout << -1 << std::endl;
            return;
        }

        // Perform cyclic shift on lls_chars: (t1 t2 ... tm) -> (tm t1 ... t(m-1))
        std::vector<char> shifted_lls_chars = lls_chars; // Make a copy to shift
        if (shifted_lls_chars.size() > 0) { // Check size before using back()
            char t_m = shifted_lls_chars.back();
            for (size_t i = shifted_lls_chars.size() - 1; i > 0; --i) {
                shifted_lls_chars[i] = shifted_lls_chars[i - 1];
            }
            shifted_lls_chars[0] = t_m;
        }
        
        // Update s_current with the shifted LLS characters
        for (size_t i = 0; i < shifted_lls_chars.size(); ++i) {
            s_current[lls_indices[i]] = shifted_lls_chars[i];
        }

        // Check if sorted after the operation
        if (is_string_sorted(s_current)) {
            std::cout << ops_performed << std::endl;
            return;
        }

        // Check if string is stuck (no change and not sorted)
        if (s_current == s_before_op) {
            std::cout << -1 << std::endl;
            return;
        }
    }

    // If loop finishes, max operations limit reached without sorting or sticking
    std::cout << -1 << std::endl;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    int t;
    std::cin >> t;
    while (t--) {
        solve_test_case();
    }
    return 0;
}

