#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

using namespace std;

// Function to check if a word contains only the given two letters
bool isValidWord(const string& word, char a, char b) {
    for (char c : word) {
        if (c != a && c != b) {
            return false;
        }
    }
    return true;
}

int main() {
    int n;
    cin >> n;
    
    vector<string> words(n);
    unordered_map<char, int> letterCount;
    //vector<pair<string, int>> wordList; 

    // Read words and count letter occurrences
    for (int i = 0; i < n; i++) {
        cin >> words[i];
        for (char c : words[i]) {
            letterCount[c]++;
        }
    }

    // Extract all unique letters
    vector<char> uniqueLetters;
    for (auto& p : letterCount) {
        uniqueLetters.push_back(p.first);
    }

    int maxLength = 0;

    // Try all pairs of letters
    int letterSize = uniqueLetters.size();
    for (int i = 0; i < letterSize; i++) {
        for (int j = i; j < letterSize; j++) {
            char a = uniqueLetters[i], b = uniqueLetters[j];
            int currentLength = 0;

            for (const string& word : words) {
                if (isValidWord(word, a, b)) {
                    currentLength += word.size();
                }
            }

            maxLength = max(maxLength, currentLength);
        }
    }

    cout << maxLength << endl;

    return 0;
}