#include <algorithm>
#include <bits/stdc++.h>
#include <cassert>
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

int N;

vector<vector<ll>> adjMatrix;
vector<ll> degree;
ll in1, in2;
int TC_ID;
vector<ll> parent(51, 0), set_size(51, 0);

ll find_set(ll a) {
    if (parent[a] == a) {
        return a;
    }
    return parent[a] = find_set(parent[a]);
}

void join_set(ll a, ll b) {
    a = find_set(a);
    b = find_set(b);
    if (a != b) {
        if (set_size[a] < set_size[b]) {
            parent[a] = b;
            set_size[b] += set_size[a];
        } else {
            parent[b] = a;
            set_size[a] += set_size[b];
        }
    }
}

bool checkEuclid(int& start) {
    FOR(i, 1, degree.size()) {
        if (degree[i] % 2 != 0) {
            return false;
        } 
        if (degree[i] > 0) {
            start = i;
        }
    }

    FOR(i, 1, degree.size()) {
        if (degree[i] > 0 && find_set(start) != find_set(i)) {
            return false;
        }
    }
    return true;
}

void dfs(ll currNode, vector<int>* path = nullptr) {
    FOR(i, 1, 51) {
        if (adjMatrix[currNode][i] != 0) {
            adjMatrix[currNode][i]--;
            adjMatrix[i][currNode]--;
            dfs(i, path);
            printf("%d %lld\n", i, currNode);
        }
    }
    if (path != nullptr) {
        path->push_back(currNode);
    }
}

void solve() {
    int start_node;
    if (checkEuclid(start_node) == false) {
        printf("some beads may be lost\n");
        return;
    }
    vector<int>* path = nullptr;
#ifdef LOCALONLY
    // cout << "Hello\n";
    path = new vector<int>;
#endif

    dfs(start_node, path);

#ifdef LOCALONLY
    cout << "Printing content" << endl;
    for (auto& v : (*path)) {
        cout << v << " ";
    }
    cout << endl;
    delete path;
#endif

}

int main() {
#ifdef LOCALONLY
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    degree.resize(51);
    adjMatrix.resize(51);
    int TC;
    scanf("%d", &TC);
    TC_ID = 0;
    FOR0(tc_idx, TC) {
        scanf("%d", &N);
        // adjList.clear();
        fill(degree.begin(), degree.end(), 0);
        fill(adjMatrix.begin(), adjMatrix.end(), vector<ll>(50, 0));
        fill(parent.begin(), parent.end(), 0);
        fill(set_size.begin(), set_size.end(), 1);
        FOR0(i, parent.size()) {
            parent[i] = i;
        }

        FOR0(i, N) {
            scanf("%lld %lld", &in1, &in2);
            degree[in2]++;
            degree[in1]++;
            adjMatrix[in1][in2]++;
            adjMatrix[in2][in1]++;
            join_set(in1, in2);
        }

        printf("Case #%d\n", tc_idx + 1);
        solve();
        if (tc_idx != TC - 1) {
            printf("\n");
        }
    }
    return 0;
}