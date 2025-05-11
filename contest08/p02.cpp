#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

// Structure to represent an item with value, weight, and density
struct Item {
    double value;
    double weight;
    double density;
};

// Comparison function to sort items by descending density
bool cmp(const Item &a, const Item &b) {
    return a.density > b.density;
}

// Function to compute maximum value of the fractional knapsack
// items: vector of Item, each with value and weight set
// W: knapsack capacity
// Returns: maximum total value (double)
double fractionalKnapsack(vector<Item> &items, double W) {
    // Compute density for each item
    for (auto &it : items) {
        it.density = it.value / it.weight;
    }
    // Sort items by density in descending order
    sort(items.begin(), items.end(), cmp);

    double totalValue = 0.0;
    double remaining = W;

    // Greedily take items
    for (auto &it : items) {
        if (remaining <= 0.0) break;

        if (it.weight <= remaining) {
            // Take whole item
            totalValue += it.value;
            remaining -= it.weight;
        } else {
            // Take fraction of the item that fits
            double fraction = remaining / it.weight;
            totalValue += it.value * fraction;
            remaining = 0.0;
            break;
        }
    }

    return totalValue;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    double W;
    // Read number of items and knapsack capacity
    cin >> n >> W;

    vector<Item> items(n);
    for (int i = 0; i < n; ++i) {
        cin >> items[i].value >> items[i].weight;
    }

    double maxValue = fractionalKnapsack(items, W);
    // Print result with two decimal places
    cout << fixed << setprecision(9) << maxValue << "\n";

    return 0;
}
