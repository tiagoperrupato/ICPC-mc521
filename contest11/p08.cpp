#include <iostream>
#include <vector>
#include <algorithm> // For std::reverse
#include <climits>   // Not strictly needed if using a large const for INF

// Using a large constant for infinity
const long long INF = 1e18; // Sufficiently large for path sums

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    std::cin >> n;

    // adj stores the initial adjacency matrix
    std::vector<std::vector<long long>> adj(n, std::vector<long long>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cin >> adj[i][j];
            if (i == j) adj[i][j] = 0; // Ensure diagonal is 0, though problem states a_ii = 0
        }
    }

    // x_removal_order stores the vertices to be removed, 1-indexed from input
    std::vector<int> x_removal_order(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> x_removal_order[i];
        x_removal_order[i]--; // Convert to 0-based indexing
    }

    // dist[i][j] stores the shortest path between i and j
    // considering only allowed intermediate vertices from those "added back" so far.
    // Initialize with the original adjacency matrix.
    std::vector<std::vector<long long>> dist = adj;

    // is_node_present[k] is true if vertex k has been "added back" and is part of the current graph
    std::vector<bool> is_node_present(n, false);
    
    // results will store the sum of shortest paths calculated at each step (in reverse order of game steps)
    std::vector<long long> results;

    // Iterate through the removal list in reverse order
    // This simulates adding vertices back one by one
    for (int p = n - 1; p >= 0; --p) {
        int k_node_added = x_removal_order[p]; // The vertex being "added back"

        // The vertex k_node_added is now considered available as an intermediate.
        // Update all shortest paths using k_node_added as a potential intermediate.
        // This is the k_node_added-th iteration of the Floyd-Warshall algorithm.
        // The dist[i][k_node_added] and dist[k_node_added][j] values are the shortest paths
        // found using vertices processed in previous iterations (x_removal_order[p+1]...x_removal_order[n-1])
        // as intermediates, or direct edge weights from the 'dist' matrix which was initialized with 'adj'.
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                 if (dist[i][k_node_added] != INF && dist[k_node_added][j] != INF) { // Check for reachability
                    long long path_via_k = dist[i][k_node_added] + dist[k_node_added][j];
                    if (path_via_k < dist[i][j]) {
                        dist[i][j] = path_via_k;
                    }
                }
            }
        }
        
        // Mark the current node k_node_added as present for the sum calculation
        is_node_present[k_node_added] = true;
        
        // Calculate the sum of shortest paths for the current set of present_nodes
        long long current_sum = 0;
        for (int i = 0; i < n; ++i) {
            if (is_node_present[i]) {
                for (int j = 0; j < n; ++j) {
                    // Sum for distinct pairs u,v where both are currently present
                    if (is_node_present[j] && i != j) { 
                        if (dist[i][j] < INF) { // Make sure path exists and is not effectively infinity
                            current_sum += dist[i][j];
                        }
                    }
                }
            }
        }
        results.push_back(current_sum);
    }

    // The results were calculated based on processing removals in reverse,
    // so the list of sums is in reverse order of the game steps. Reverse it.
    std::reverse(results.begin(), results.end());

    for (size_t i = 0; i < results.size(); ++i) {
        std::cout << results[i] << (i == results.size() - 1 ? "" : " ");
    }
    std::cout << std::endl;

    return 0;
}

