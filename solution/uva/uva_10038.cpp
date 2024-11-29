#include <bits/stdc++.h>
#include <ios>
using namespace std;

/******* Set up *******/
#define FOR(i, L ,R) for (int i = L; i < R; i++)
#define FOR0(i, N) for (int i = 0; i < N; i++)
#define endl "\n"
using ll=long long;
using vi = vector<int>;
using vii = vector<vector<int>>;
/**********************/

vector<bool> check(3010, 0);

int main() {
#ifdef LOCALONLY
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    int n, curr, prev;
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(0);
    while (cin >> n) {
        check.resize(n);
        fill(check.begin(), check.end(), false);
        cin >> curr;
        prev = curr;
        FOR(i, 1, n) {
            cin >> curr;
            int diff = abs(curr - prev);
            if (diff > n) {
                check[i] = false;
                break;
            } else {
                check[diff] = true;
            }
            prev = curr;
        }

        bool bJolly = true;
        FOR(i, 1, n) {
            if (!check[i]) {
                bJolly = false;
                break;
            }
        }
        cout << (bJolly ? "Jolly" : "Not jolly") << "\n";
    }

    return 0;
}