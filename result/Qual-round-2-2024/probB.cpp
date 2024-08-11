#include <bits/stdc++.h>
using namespace std;

/******* Set up *******/
#define FOR(i, L ,R) for (int i = L; i < R; i++)
#define FOR0(i, N) for (int i = 0; i < N; i++)
#define endl "\n"
using ll=long long;
using vi = vector<int>;
using vii = vector<vector<int>>;
/**********************/

#define LIM (LLONG_MAX / 2)

ll minPath, maxPath;

ll N;
ll arr[10][10][10];

int counter;

const ll CACHE_SIZE = ((2 << 8) + 1);

ll cache[9][CACHE_SIZE][CACHE_SIZE];
ll filled[9][CACHE_SIZE][CACHE_SIZE];

ll solveMin(int city, ll transMask, ll cityMask) {
    if (cityMask == ((1 << N) - 1)) {
        FOR0(i, N) {
            if ((transMask & (1 << i)) == 0 && arr[i][city][0] != 0) {
                return arr[i][city][0];
            }
        }
        return LIM;
    }

    if (filled[city][transMask][cityMask] == counter) {
        return cache[city][transMask][cityMask];
    }

    ll cost = 0;
    ll res = LIM;

    FOR0(i , N) {
        if ((cityMask & ( 1 << i )) != 0) {
            continue;
        }
        ll newCityMask = (cityMask | (1 << i));
        FOR0(j, N) {
            if ((transMask & (1 << j)) == 0 &&  arr[j][city][i] != 0) {
                ll newTransMask = (transMask | (1 << j));
                cost = arr[j][city][i] + solveMin(i, newTransMask, newCityMask);
                if (cost < res) {
                    res = cost;
                }
            }
        }
    }
    filled[city][transMask][cityMask] = counter;
    cache[city][transMask][cityMask] = res;
    return res;
}

ll solveMax(int city, ll transMask, ll cityMask) {
    if (cityMask == ((1 << N) - 1)) {
        FOR0(i, N) {
            if ((transMask & (1 << i)) == 0 && arr[i][city][0] != 0) {
                return arr[i][city][0];
            }
        }
        return LLONG_MIN;
    }
    if (filled[city][transMask][cityMask] == counter) {
        return cache[city][transMask][cityMask];
    }
    ll res = -1000000000;

    FOR0(i , N) {
        if ((cityMask & ( 1 << i )) > 0) {
            continue;
        }
        ll newCityMask = (cityMask | (1 << i));
        FOR0(j, N) {
            if ((transMask & (1 << j)) == 0 &&  arr[j][city][i] != 0) {
                ll newTransMask = (transMask | (1 << j));
                ll cost = arr[j][city][i] + solveMax(i, newTransMask, newCityMask);
                if (cost > res) {
                    res = cost;
                }
            }
        }
    }
    filled[city][transMask][cityMask] = counter;
    cache[city][transMask][cityMask] = res;
    return res;
}

int main() {
#ifdef LOCALONLY
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    //Filled cache
    counter = 0;
    FOR0(i, 9) {
        FOR0(j, CACHE_SIZE) {
            FOR0(k, CACHE_SIZE) {
                filled[i][j][k] = -1;
            }
        }
    }

    int TC;
    scanf("%d", &TC);
    while (TC--) { 

#ifdef LOCALONLY
    static int _tc_num = 1;
    cout << "Testcase " << _tc_num << ":\n";
    _tc_num++;
#endif

        scanf("%lld", &N);
        FOR0(i, N) {
            FOR0(j, N) {
                FOR0(k, N) {
                    scanf("%lld", &arr[i][j][k]);
                }
            }
        }

        ll cityMask = 1;
        ll transMask = 0;
        minPath = solveMin(0, transMask, cityMask);
        minPath = (minPath == LIM) ? 0 : minPath;
        counter++;

        maxPath = solveMax(0, transMask, cityMask);
        maxPath = (maxPath < 0) ? 0 : maxPath;
        counter++;

        printf("%lld %lld", minPath, maxPath);
        if (TC >= 0) {
            printf("\n");
        }
    }
    return 0;
}