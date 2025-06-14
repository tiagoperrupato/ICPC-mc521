#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int w, l;
    std::cin >> w >> l;

    std::vector<long long> a(w - 1);
    for (int i = 0; i < w - 1; ++i) {
        std::cin >> a[i];
    }

    long long current_stones = 0;
    for (int i = 0; i < l; ++i) {
        current_stones += a[i];
    }

    long long min_stones = current_stones;

    // Slide the window from the start to the end of the river.
    // The window moves one step at a time until it reaches the end.
    for (int i = l; i < w - 1; ++i) {
        current_stones += a[i] - a[i - l];
        
        // Update the minimum if the current window's sum is smaller.
        min_stones = std::min(min_stones, current_stones);
    }

    std::cout << min_stones << std::endl;

    return 0;
}