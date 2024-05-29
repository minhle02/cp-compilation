#include <bits/stdc++.h>
#include <vector>
using namespace std;

/******* Set up *******/
#define FOR(i, L, R) for (int i = L; i < R; i++)
#define FOR0(i, N) for (int i = 0; i < N; i++)
#define endl "\n"
using ll = long long;
using vi = vector<int>;
using vii = vector<vector<int>>;
/**********************/

class DSU {
public:
  vi parent;
  vi size;
  int numSets;

public:
  DSU(int N = 0) : numSets(N) {
    parent.assign(N, 0);
    for (int i = 0; i < N; i++)
      parent[i] = i;
    size.assign(N, 0);
  }
  int find_set(int n) {
    if (n == parent[n])
      return n;

    parent[n] = find_set(parent[n]);
    return parent[n];
  }

  void make_set(int v) {
    parent[v] = v;
    size[v] = 1;
  }

  void union_sets(int a, int b) {
    a = find_set(a);
    b = find_set(b);
    if (a == b)
      return;

    if (size[a] < size[b]) {
      parent[a] = b;
      size[b] += size[a];
    } else {
      parent[b] = a;
      size[a] += size[b];
    }
  }

  bool is_same(int a, int b) { return find_set(a) == find_set(b); }
};

ll N, K;
ll query[3] = {0LL, 0LL, 0LL};
int counter = 0;

void solve(DSU &data, unordered_map<int, vector<int> > &eaten) {
  if (query[1] < 0 || query[1] >= N || query[2] < 0 || query[2] >= N) {
    counter++;
    return;
  }
  int a = data.find_set(query[1]);
  int b = data.find_set(query[2]);
  if (query[0] == 1) {
    if (a == b) {
      return;
    }
  }
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
    scanf("%lld %lld", &N, &K);
    DSU data(N);
    for (int i = 0; i < K; i++) {
      scanf("%lld %lld %lld", &query[0], &query[1], &query[2]);
      query[1]--;
      query[2]--;
      solve(data);
    }
    printf("%d", counter);
    if (TC >= 0) {
      printf("\n");
    }
  }
  return 0;
}