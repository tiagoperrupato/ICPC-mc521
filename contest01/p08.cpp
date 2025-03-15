#include <iostream>
#include <queue>
#include <unordered_set>

using namespace std;

// Function to find the smallest multiple of n consisting of only 0s and 1s
string findSmallestMultiple(int n) {
    if (n == 1) return "1";

    queue<pair<string, int>> q;  // Queue to store (number as string, remainder mod n)
    unordered_set<int> visited;  // Set to store visited remainders

    q.push({"1", 1 % n});
    visited.insert(1 % n);

    while (!q.empty()) {
        auto [num, remainder] = q.front();
        q.pop();
        if (num.size() > 100) break;  // Stop searching multiple
        if (remainder == 0) return num;  // Found the answer

        // Append '0' and '1' to the number
        for (char digit : {'0', '1'}) {
            string newNum = num + digit;
            int newRemainder = (remainder * 10 + (digit - '0')) % n;

            if (visited.find(newRemainder) == visited.end()) {
                q.push({newNum, newRemainder});
                visited.insert(newRemainder);
            }
        }
    }

    return "BRAK";  // Should never reach here for valid inputs
}

int main() {
    int t;
    cin >> t;
    
    while (t--) {
        int n;
        cin >> n;
        cout << findSmallestMultiple(n) << endl;
    }

    return 0;
}