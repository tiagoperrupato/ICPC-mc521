def solve():
    t = int(input())
    for _ in range(t):
        n = int(input())
        if n % 2 == 0:
            print(-1)
        else:
            p = [ (2*i) % n + 1 for i in range(n) ]
            print(*p)

if __name__ == "__main__":
    solve()