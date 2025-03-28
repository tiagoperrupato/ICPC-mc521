#include <iostream>
#include <vector>
#include <string>

using namespace std;

void generatePermutations(string prefix, string remaining, vector<string>& permutations) {
    if (remaining.length() == 0) {
        permutations.push_back(prefix);
        return;
    }

    for (size_t i = 0; i <= prefix.length(); ++i) {
        string newPrefix = prefix.substr(0, i) + remaining[0] + prefix.substr(i);
        generatePermutations(newPrefix, remaining.substr(1), permutations);
    }
}

int main() {
    string input;

    cin >> input;
    vector<string> permutations;
    generatePermutations("", input, permutations);

    for (const string& perm : permutations) {
        cout << perm << endl;
    }

    while (cin >> input) {
        cout << endl;
        vector<string> permutations;
        generatePermutations("", input, permutations);

        for (const string& perm : permutations) {
            cout << perm << endl;
        }
    }

    return 0;
}