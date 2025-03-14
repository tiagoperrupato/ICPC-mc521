#include <iostream>
#include <vector>
#include <set>

using namespace std;

int countFaces(const vector<string>& image, int n, int m) {
    int count = 0;
    string face = "face";
    
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < m - 1; ++j) {
            set<char> letters = { image[i][j], image[i][j + 1], image[i + 1][j], image[i + 1][j + 1] };
            if (letters.size() == 4 && letters.count('f') && letters.count('a') && letters.count('c') && letters.count('e')) {
                count++;
            }
        }
    }
    
    return count;
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<string> image(n);
    
    for (int i = 0; i < n; ++i) {
        cin >> image[i];
    }
    
    cout << countFaces(image, n, m) << endl;
    return 0;
}