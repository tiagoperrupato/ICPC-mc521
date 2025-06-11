import sys
import heapq

def find_min_delay_path(n, adj, start, end):
    # dist[i]: best known total delay to reach i
    dist = [float('inf')] * (n + 1)
    prev = [None] * (n + 1)        # to reconstruct path
    dist[start] = 0

    # min-heap of (current_delay, node)
    heap = [(0, start)]
    while heap:
        d, u = heapq.heappop(heap)
        if d > dist[u]:
            continue
        if u == end:
            break
        for v, delay_at_v in adj[u]:
            nd = d + delay_at_v
            if nd < dist[v]:
                dist[v] = nd
                prev[v] = u
                heapq.heappush(heap, (nd, v))

    # reconstruct path from start to end
    if dist[end] == float('inf'):
        return None, None
    path = []
    cur = end
    while cur is not None:
        path.append(cur)
        cur = prev[cur]
    path.reverse()
    return path, dist[end]


def main():
    data = sys.stdin.read().strip().split()
    it = iter(data)
    case_num = 1

    while True:
        ni = int(next(it))
        if ni == 0:
            break

        # build adjacency list: for each intersection u, list of (v, delay_at_v)
        adj = {i: [] for i in range(1, ni+1)}
        for u in range(1, ni+1):
            m = int(next(it))
            for _ in range(m):
                v = int(next(it))
                delay = int(next(it))
                adj[u].append((v, delay))

        start = int(next(it))
        end   = int(next(it))

        path, total_delay = find_min_delay_path(ni, adj, start, end)

        # output
        path_str = " ".join(str(x) for x in path)
        print(f"Case {case_num}: Path = {path_str}; {total_delay} second delay")
        case_num += 1

if __name__ == "__main__":
    main()