#include <bits/stdc++.h>
#include <cassert>
#include <thread>
using namespace std;

/******* Set up *******/
#define FOR(i, L ,R) for (ll i = L; i < R; i++)
#define FOR0(i, N) for (ll i = 0; i < N; i++)
#define endl "\n"
using ll=long long;
using vi = vector<int>;
using vii = vector<vector<int>>;
/**********************/

#define ARR_SIZE 65010
#define DSIZE 65000

ll Na, Ma;
ll Nb, Mb;

vector<ll> Sa, Sb;

vector<vector<ll>> listA, listB;

vector<ll> distA, distB;
vector<ll> isSpecialA, isSpecialB;

vector<ll> nodeSubTreeA, nodeSubTreeB;

ll visited[ARR_SIZE + 1];
ll linkTo[ARR_SIZE + 1];
ll countArr[ARR_SIZE + 1];
ll countNode[ARR_SIZE + 1];

ll idxCount = 0;

ll p1, p2;

static ll counter = 0;

void AddList(vector<vector<ll>>& i_list, ll from, ll to) {
    from--;
    to--;
    i_list[from].push_back(to);
    i_list[to].push_back(from);
}

ll dfs4(vector<vector<ll>>& i_list, vector<ll>& i_special, ll parent, ll curr) {
    ll res = 1;
    for (ll i : i_list[curr]) {
        if (i != parent && i_special[i] == 0) {
            res += dfs4(i_list, i_special, curr, i);
        }
    }
    return res;
}

void dfs5(vector<vector<ll>>& i_list, vector<ll>& i_special, vector<ll>& i_nodeSubTree, ll parent, ll curr, ll& val) {
    linkTo[curr] = idxCount;
    i_nodeSubTree[curr] = val;
    visited[curr] = counter;

    for (ll i : i_list[curr]) {
        if (i != parent && i_special[i] == 0) {
            dfs5(i_list, i_special, i_nodeSubTree, curr, i, val);
        }
    }
}

void fillDist(vector<vector<ll>>& i_list, vector<ll>& i_special, vector<ll>& i_spList, vector<ll>& i_dist, vector<ll>& i_nodeSubTree) {
    
    counter += 2;
    FOR0(i, i_list.size()) {
        if (i_special[i] == 0 && visited[i] != counter) {
            countArr[idxCount] = 0;
            ll temp = dfs4(i_list, i_special, -1, i);
            dfs5(i_list, i_special, i_nodeSubTree, -1, i, temp);
            idxCount++;
        }
    }

    for (ll p : i_spList) {
        ll numNodes = 1;
        for (ll i : i_list[p]) {
            if (i_special[i] == 0) {
                numNodes = numNodes + i_nodeSubTree[i];
            }
        }

        for (ll i : i_list[p]) {
            if (i_special[i] == 0) {
                countArr[linkTo[i]] += (numNodes - i_nodeSubTree[i]);
            }
        }
        i_nodeSubTree[p] = numNodes;
        i_dist[p] = numNodes;
    }

    // Filling dist
    FOR0(k, (i_dist.size())) {
        if (i_special[k] == 0) {
            i_dist[k] = countArr[linkTo[k]];
        }
    }
}

void PrintDist(vector<ll>& i_dist) {
    FOR0(i, i_dist.size()) {
        cout << i_dist[i] << " ";
    }
    cout << endl;
}

ll solve() {
    idxCount = 0;
    fillDist(listA, isSpecialA, Sa, distA, nodeSubTreeA);
    idxCount = 0;
    fillDist(listB, isSpecialB, Sb, distB, nodeSubTreeB);

#ifdef DEBUG
    PrintDist(distA);
    PrintDist(distB);
#endif

    ll res = 0;
    const ll MOD = 1000000007;

    ll sumA = 0;
    ll sumB = 0;

    FOR0(i, Na) {
        assert(distA[i] != 0);
        sumA += distA[i];
    }

    FOR0(i, Nb) {
        assert(distB[i] != 0);
        sumB += distB[i];
    }
    sumA = sumA % MOD;
    sumB = sumB % MOD;

    ll expA = 0;
    ll expB = 0;

    FOR0(i, Na) {
        expA += distA[i]*(i + 1);
        expA = expA % MOD;
    }

    FOR0(i, Nb) {
        expB += distB[i]*(i + 1);
        expB = expB % MOD;
    }

    res = (expA * sumB) % MOD + (expB * sumA) % MOD;
    return res % MOD;
} 

int main() {
#ifdef LOCALONLY
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    FOR0(i, ARR_SIZE + 2) {
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
        idxCount = 0;
        scanf("%lld %lld", &Na, &Ma);

        listA.resize(Na);
        fill(listA.begin(), listA.end(), vector<ll>{});

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
        }
        
        FOR0(i, Na - 1) {
            scanf("%lld %lld", &p1, &p2);
            AddList(listA, p1, p2);
        }

        scanf("%lld %lld", &Nb, &Mb);

        listB.resize(Nb);
        fill(listB.begin(), listB.end(), vector<ll>{});
    
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
        }
        
        FOR0(i, Nb - 1) {
            scanf("%lld %lld", &p1, &p2);
            AddList(listB, p1, p2);
        }

        printf("%lld", solve());
        if (TC >= 1) {
            printf("\n");
        }
    }
    return 0;
}