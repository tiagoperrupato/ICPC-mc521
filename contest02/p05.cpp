#include <iostream>
#include <vector>
#include <set>
#include <sstream>
#include <algorithm>

using namespace std;

string standardizeSequence(const string &input) {
    set<int> pages;
    stringstream ss(input);
    string token;
    
    // Parse input and insert unique page numbers into the set
    while (getline(ss, token, ',')) {
        pages.insert(stoi(token));
    }
    
    // Convert set to sorted vector
    vector<int> sortedPages(pages.begin(), pages.end());
    
    stringstream result;
    int n = sortedPages.size();
    
    for (int i = 0; i < n; ) {
        int start = sortedPages[i], end = start;
        
        // Find contiguous sequence
        while (i + 1 < n && sortedPages[i + 1] == sortedPages[i] + 1) {
            end = sortedPages[i + 1];
            i++;
        }
        
        // Append to result in required format
        if (!result.str().empty()) result << ",";
        if (start == end)
            result << start;
        else
            result << start << "-" << end;
        
        i++;
    }
    
    return result.str();
}

int main() {
    string input;
    cin >> input;
    cout << standardizeSequence(input) << endl;
    return 0;
}
