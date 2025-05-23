#include <iostream>
#include <cmath>
#include <cstdio>
#include <vector>

using namespace std;

typedef vector <int> vi;

class SegmentTree { // the segment tree is stored like a heap array
    private: 
        vi st , A; // recall that vi is : typedef vector <int> vi;
        int n;

        int left(int p) { return p << 1; } // same as binary heap operations

        int right(int p) { return ( p << 1) + 1; }

        void build (int p , int L , int R) { // O(n)
            if (L == R) // as L == R, either one is fine
                st[p] = L ; // store the index

            else { // recursively compute the values
                build(left(p) , L , (L + R)/2);
                build(right(p) , (L + R)/2 + 1, R);

                int p1 = st[left(p)], p2 = st[right(p)];
                st[p] = (A[p1] <= A[p2]) ? p1 : p2;
            } 
        }

        int rmq (int p , int L , int R, int i , int j) { // O( log n )
            if (i > R || j < L) return -1; // current segment outside query range

            if (L >= i && R <= j) return st[p]; // inside query range

            // compute the min position in the left and right part of the interval
            int p1 = rmq(left(p), L, (L + R)/2, i, j);
            int p2 = rmq(right(p), (L + R)/2 + 1, R, i, j);

            if (p1 == -1) return p2; // if we try to access segment outside query
            if (p2 == -1) return p1; // same as above
            return (A[p1] <= A[p2]) ? p1 : p2;
        } // as in build routine

    public:
        SegmentTree ( const vi &_A) {
            A = _A ; n = (int)A.size(); // copy content for local usage
            st.assign (4 * n , 0); // create large enough vector of zeros
            build(1, 0, n - 1); // recursive build
        }

        int rmq(int i, int j) { return rmq(1, 0, n - 1, i, j); } // overloading
};

int main() {
    int t, n, q, l, r;
    cin >> t;
    for (int i = 0; i < t; i++) {
        cin;
        cin >> n >> q;
        int arr[n];
        for (int j = 0; j < n; j++) {
            cin >> arr[j];
        }
        vi A(arr, arr + n);
        SegmentTree st(A);

        cout << "Case " << i + 1 << ":" << endl;
        for (int j = 0; j < q; j++) {
            cin >> l >> r;
            cout << A[st.rmq(l - 1, r - 1)] << endl;
        }
    }

    return 0;
}