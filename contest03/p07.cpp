#include <iostream>
using namespace std;

int main()
{
    cin.sync_with_stdio(0);
    cin.tie(0);

    int N;
    cin >> N;
    for (int i = 0; i < N; i++)
    {
        int A, B, C;
        cin >> A >> B >> C;
        bool sol = false;
        int x, y, z;
        for (x = -21; x <= 21 && !sol; x++) {
            if (x * x <= C) {
                for (y = x + 1; y <= 100 && !sol; y++) {
                    if (x * x + y * y <= C) {
                        for (z = y + 1; z <= 100 && !sol; z++) {
                            if (x + y + z == A && x * y * z == B && x * x + y * y + z * z == C) {
                                cout << x << " " << y << " " << z << endl;
                                sol = true;
                            }
                        }
                    }
                }
            }
        }

        if (!sol)
            cout << "No solution." << endl;
    }
    return 0;
}
