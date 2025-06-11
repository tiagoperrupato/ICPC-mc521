def f(k: int, A: list[int], l: int, r: int) -> int:
    ans = 0

    for i in range(l-1, r):
        while k % A[i] == 0:
            k = k / A[i]
        ans = ans + k

    return ans

def main():
    testcases = int(input())

    for _ in range(testcases):
        n, q = map(int, input().split())
        A = list(map(int, input().split()))

        for query in range(q):
            k, l, r = map(int, input().split())
            print(int(f(k, A, l, r)))

main()

