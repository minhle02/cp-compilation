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

ll N, X;
int lenNum;
ll num[35];
ll V[4010];

char s[20] = {'\0'};

ll number[20][20];

ll lenEq;
vector<vector<ll>> equationList((2 << 15) + 10, vector<ll>(40, 0));

ll evalRes[3];

void eval() {
    ll res = 0;
    ll curr = 0;
    ll countP = 0;
    ll firstSpace = 100;
    FOR(i, 0, lenNum) {
        if (i % 2 == 0) {
            curr = curr * 10 + num[i];
#ifdef DEBUG
            cout << num[i];
#endif
        } else if (num[i] == -1) {
            continue;
        } else {
#ifdef DEBUG
            cout << " + ";
#endif
            countP++;
            res += curr;
            curr = 0;
        }
    }
    if (curr != 0) {
        res += curr;
    }
#ifdef DEBUG
            cout << "\t--\t" << res << endl;
#endif
    equationList[lenEq][0] = res;
    equationList[lenEq][1] = countP;
    FOR(i, 0, lenNum) {
        equationList[lenEq][2 + i] = num[i];
        // if (equationList[lenEq][2 + i] == -2) {
        //     cout << "+";
        // } else if(equationList[lenEq][2 + i] == -1) {
        //     cout << " ";
        //     continue;
        // } else {
        //     cout << equationList[lenEq][2 + i];
        // }
    }
    // cout << endl;
    // memcpy(&equationList[lenEq][2], num, 35);
    return;
}

void fillEq(int index) {
    if (index >= lenNum) {
        eval();
        // ll sumArr = evalRes[0];
        // ll countPlus = evalRes[2];
        // ll firstSpace = evalRes[1];

        // FOR(i, 0, lenNum) {
        //     //  equationList[lenEq][2 + i] = num[i];
        //     if (equationList[lenEq][2 + i] == -2) {
        //         cout << "+";
        //     } else if(equationList[lenEq][2 + i] == -1) {
        //         cout << " ";
        //         continue;
        //     } else {
        //         cout << equationList[lenEq][2 + i];
        //     }
        // }
        // cout << endl;
        
#ifdef DEBUG
        cout << equationList[lenEq][0] << " " << equationList[lenEq][1] << " - ";
        FOR(i, 0, lenNum) {
            if (i % 2 == 1) {
                if (equationList[lenEq][2 + i] == -1) continue;
                cout << "+";
                continue;
            }
            cout << equationList[lenEq][2 + i] << " ";
        }
        cout << endl << endl;
#endif
        lenEq++;
        return;
    }
    // skip:
    fillEq(index + 2);
    // take
    num[index] = -2;
    fillEq(index + 2);
    num[index] = -1;
}

void solve() {
    fillEq(1);
    sort(equationList.begin(), equationList.begin() + lenEq, [](vector<ll>& lhs, vector<ll>& rhs) {
        if (lhs[0] != rhs[0]) {
            return lhs[0] < rhs[0];
        } else {
            for (int i = 1; i < lenNum; i += 2) {
                if (lhs[2 + i] != rhs[2 + i]) {
                    return lhs[2 + i] < rhs[2 + i];
                }
            }
            return true;
        }
    });

    ll Ws = 0;
    ll Wp = 0;
    FOR0(i, N) {
        Ws += equationList[V[i]][0];
        Wp += equationList[V[i]][1];
    }
    printf("%lld %lld", Ws, Wp);
    return;
}


int main() {
#ifdef LOCALONLY
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    int TC;
    scanf("%d", &TC);
    while (TC--) { 
#ifdef LOCALONLY
    static int _tc_num = 1;
    cout << "Testcase " << _tc_num << ":\n";
    _tc_num++;
#endif

        scanf("%lld", &N);
        scanf("%s", &s[0]);
        // cout << s << endl;
        lenNum = 0;
        lenEq = 0;
        for (int i = 0; i < 35 && s[i / 2] != '\0'; i += 2) {
            lenNum += 2;
            num[i] = s[i / 2] - '0';
            num[i + 1] = -1;
        }
        lenNum--;
        
        FOR(i, 0, N) {
            scanf("%lld", V + i);
            V[i]--;
        }

        // FOR0(i, lenNum) {
        //     cout << num[i] << " ";
        // }
        solve();
        if (TC >= 0) {
            printf("\n");
        }

        // getNumber();
    }
    return 0;
}