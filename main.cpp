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

#define ARR_SIZE 65010
#define DSIZE 65000

ll Na, Ma;
ll Nb, Mb;

// ll Sa[ARR_SIZE + 1];
// ll Sb[ARR_SIZE + 1];

vector<ll> Sa, Sb;

map<ll, vector<ll>> listA, listB;

vector<ll> distA, distB;
vector<ll> isSpecialA, isSpecialB;

vector<ll> nodeSubTreeA, nodeSubTreeB;

ll visited[ARR_SIZE + 1];
ll linkTo[ARR_SIZE + 1];
ll countArr[ARR_SIZE + 1];
ll countNode[ARR_SIZE + 1];


ll p1, p2;

ll counter = 0;

void AddList(map<ll, vector<ll>>& i_list, ll from, ll to) {
    i_list[from].push_back(to);
    i_list[to].push_back(from);
}

void dfs3(map<ll, vector<ll>>& i_list, vector<ll>& i_special, vector<ll>& i_numNodes, ll parent, ll curr) {

    linkTo[curr] = countArr[ARR_SIZE];
    visited[curr] = counter;
    i_numNodes[curr]++;
    for (ll i : i_list[curr]) {
        if (i == parent || i_special[i] == 1 || visited[i] == counter) {
            continue;
        }
        dfs3(i_list, i_special, i_numNodes, curr, i);
        i_numNodes[curr] += i_numNodes[i];
        i_numNodes[i] = i_numNodes[curr];
    }
}

void fillDist(map<ll, vector<ll>>& i_list, vector<ll>& i_special, vector<ll>& i_spList, vector<ll>& i_dist, vector<ll>& i_nodeSubTree) {
    
    counter++;
    for (auto p : i_spList) {
        for (auto i : i_list[p]) {
            if (visited[i] != counter) {
                countArr[countArr[ARR_SIZE]] = 0;
                dfs3(i_list, i_special, i_nodeSubTree, -1, i);
                countNode[countArr[ARR_SIZE]] = i_nodeSubTree[i];
                countArr[ARR_SIZE]++;
            }
        }
    }
    
    // cout << "Node:" << endl;
    // for (auto i : i_nodeSubTree) {
    //     cout << i << " ";
    // }
    // cout << endl;
    // vector<ll> nodeSubTree(i_list.size(), 0);
    for (ll i : i_spList) {
        // Get num nodes;
        ll numNodes = 1;
        for (ll p : i_list[i]) {
            if (i_special[p] == 0) {
                // ll update = linkTo[p];
                // i_nodeSubTree[p] = countNode[update];
                numNodes += i_nodeSubTree[p];
            }
        }

        for (ll p : i_list[i]) {
            ll update = linkTo[p];
            countArr[update] += numNodes - i_nodeSubTree[p];
        }
        i_dist[i] = numNodes;
    }

    // Filling dist
    FOR0(i, Na) {
        if (i_special[i] == 1) {
            continue;
        }
        if (visited[i] != counter) {
            i_dist[i] = 0;
            continue;
        }
        i_dist[i] = countArr[linkTo[i]];
    }
}

void PrintDist(vector<ll>& i_dist) {
    FOR0(i, i_dist.size()) {
        cout << i_dist[i] << " ";
    }
    cout << endl;
}

ll solve() {

    fillDist(listA, isSpecialA, Sa, distA, nodeSubTreeA);
    fillDist(listB, isSpecialB, Sb, distB, nodeSubTreeB);

#ifdef DEBUG
    PrintDist(distA);
    PrintDist(distB);
#endif

    ll res = 0;
    const ll MOD = static_cast<ll>(10e9 + 7);

    ll sumA = 0;
    ll sumB = 0;

    FOR0(i, Na) {
        sumA = (sumA % MOD) +  (distA[i] % MOD);
    }

    FOR0(i, Nb) {
        sumB = sumB % MOD + distB[i] % MOD;
    }

    sumA = sumA % MOD;
    sumB = sumB % MOD;

    FOR0(i, Na) {
        ll temp = (distA[i] * (i + 1)) % MOD;
        res = res % MOD + (temp * sumB) % MOD;
    }
    FOR0(i, Nb) {
        ll temp = (distB[i] * (i + 1)) % MOD;
        res = res % MOD + (temp * sumA) % MOD;
    }
    res = res % MOD;

    return res;
} 

int main() {
#ifdef LOCALONLY
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    FOR0(i, ARR_SIZE + 1) {
        visited[i] = -1;
    }

    int TC;
    scanf("%d", &TC);
    while (TC--) { 
#ifdef LOCALONLY
    static int _tc_num = 1;
    cout << "Testcase " << _tc_num << ":\n";
    _tc_num++;
#endif
        linkTo[ARR_SIZE] = 0;
        countArr[ARR_SIZE] = 0;
        listA.clear();
        listB.clear();
        scanf("%lld %lld", &Na, &Ma);
        distA.resize(Na);
        isSpecialA.resize(Na);
        nodeSubTreeA.resize(Na);
        fill(distA.begin(), distA.end(), 0);
        fill(isSpecialA.begin(), isSpecialA.end(), 0);
        fill(nodeSubTreeA.begin(), nodeSubTreeA.end(), 0);
        Sa.resize(Ma);


        FOR0(i, Ma) {
            scanf("%lld", &Sa[i]);
            Sa[i]--;
            isSpecialA[Sa[i]] = 1;
            // distA[Sa[i]] = 0;
        }
        
        FOR0(i, Na - 1) {
            scanf("%lld %lld", &p1, &p2);
            AddList(listA, p1 - 1, p2 - 1);
        }

        scanf("%lld %lld", &Nb, &Mb);
    
        distB.resize(Nb);
        isSpecialB.resize(Nb);
        nodeSubTreeB.resize(Nb);
        fill(distB.begin(), distB.end(), 0);
        fill(isSpecialB.begin(), isSpecialB.end(), 0);
        fill(nodeSubTreeB.begin(), nodeSubTreeB.end(), 0);
        Sb.resize(Mb);

        FOR0(i, Mb) {
            scanf("%lld", &Sb[i]);
            Sb[i]--;
            isSpecialB[Sb[i]] = 1;
            // distB[Sb[i]] = 1;
        }
        
        FOR0(i, Nb - 1) {
            scanf("%lld %lld", &p1, &p2);
            AddList(listB, p1 - 1, p2 - 1);
        }
        // if (_tc_num == 6) {
        //     for (auto& p : listA) {
        //         cout << p.first << ":\t";
        //         for (auto i : p.second) {
        //             cout << i << " ";
        //         }
        //         cout << endl;
        //     }
        //     cout << "special a: " << endl;
        //     for(auto& p : isSpecialA) {
        //         cout << p << " ";
        //     }
        //     cout << endl;
        // }
        printf("%lld\n", solve());
    }
    return 0;
}