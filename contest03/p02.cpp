#include <iostream>
#include <vector>
#include <set>
using namespace std;

int count_valid_triplets(vector<pair<int, int>> &points) {
    int n = points.size();
    int counter = 0;
    set<pair<int, int>> points_set(points.begin(), points.end()); // Store points for quick lookup

    // Iterate through all pairs of points (A, C)
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            // Compute the midpoint (B_x, B_y)
            if ((points[i].first + points[j].first) % 2 == 0 &&
                (points[i].second + points[j].second) % 2 == 0) {
                
                int mid_x = (points[i].first + points[j].first) / 2;
                int mid_y = (points[i].second + points[j].second) / 2;

                // Check if midpoint exists in the set
                if (points_set.count({mid_x, mid_y})) {
                    counter++;
                }
            }
        }
    }
    
    return counter;
}

int main() {
    cin.sync_with_stdio(0); 
    cin.tie(0);

    int n;
    cin >> n;

    vector<pair<int, int>> points(n);
    for (int i = 0; i < n; i++) {
        cin >> points[i].first >> points[i].second;
    }

    cout << count_valid_triplets(points) << endl;

    return 0;
}