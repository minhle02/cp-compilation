# Snippet

## Quick type

```
using ll = long long;
using vl = vector<long long>;
using vll = vector<vector<long long>>;
using vi = vector<int>;
using vii = vector<vector<int>>;

#define FOR(i, L ,R) for (long long i = L; i < R; i++)
#define FOR0(i, N) for (long long i = 0; i < N; i++)
#define endl "\n"
```

```
#ifdef LOCALONLY
    static int _tc_num = 1;
    cout << "Testcase " << _tc_num << ":\n";
    _tc_num++;
#endif
```

## Debug

```
void Print_Arr(ll* _n, int _l) {
    for (int i = 0; i < _l; i++) {
        cout << _n[i] << " ";
    }
    cout << endl;
}
```

# Algorithm - Basic

## Sparse Table
```
#define NC 250010
#define MAX_EXPO 20

ll sparse_table[MAX_EXPO][NC];

void gen_lcm_table() {
    FOR0(i, cc_idx){
        sparse_table[0][i] = cc[i];
    }

    ll expo = floor(log2(cc_idx)) + 1;

    FOR(i, 1, expo) {
        for (int j = 0; j + (1 << i) <= cc_idx; j++) {
            sparse_table[i][j] = lcm(sparse_table[i - 1][j], sparse_table[i - 1][j + (1 << (i - 1))]);
        }
    }
}

ll query(ll l, ll r) {
    if (r < l) {
        return 1LL;
    }
    ll len = r - l + 1;
    ll e = floor(log2(len));
    return lcm(sparse_table[e][l], sparse_table[e][r - (1 << e) + 1]);
}
```

## Disjoint Set Union
```
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
```

# Algorithm - Graphs

## Shortest Path

### BF Shortest Path

```
#define LIM 1000000000LL
#define LENGTH_BITS 20
#define COOR_BITS 10

#define MOVES 4;
int moveX[MOVES] = {0, 0, 1, -1};
int moveY[MOVES] = {1, -1, 0, 0};

int maskXY = ((1 << COOR_BITS) - 1);
int maskLength = ((1 << LENGTH_BITS) - 1);

vector<int> estimated(N, LIM);
queue<int64_t> toVisit;
int64_t pX, pY, pL;
while (!toVisit.empty()) {
    int size = toVisit.size();
    while (size-- > 0) {
        int64_t p = toVisit.front();
        toVisit.pop();
        pL = p & maskLength;
        pY = (p >> LENGTH_BITS) & maskXY;
        pX = (p >> (LENGTH_BITS + COOR_BITS)); 
        for (int i = 0; i < MOVES; i++) {
            int64_t newX = pX + moveX[i];
            int64_t newY = pY + moveY[i];
        }
    }
}
```

### Djikstra Shortest Path
```
using pii = pair<int, int>;
#define LIM 1000000
typedef struct comp {
    bool operator() (pii& lhs, pii& rhs) {
        return lhs.second > rhs.second;
    }
} comp;
    

// n : list length
// list : adj list

vector<int> estimated(n, LIM);
estimated[k - 1] = 0;
priority_queue<pii, vector<pii>, comp> pq;
pq.push(make_pair(k - 1, 0));
while (!pq.empty()) {
    auto p = pq.top();
    pq.pop();
    if (estimated[p.first] < p.second) {
        continue;
    }
    for (auto& v : list[p.first]) {
        if (p.second + v.second < estimated[v.first]) {
            estimated[v.first] = p.second + v.second;
            pq.push(make_pair(v.first, estimated[v.first]));
        }
    }
}
```

### All pair shortest path
```
n = graph.size();
vector<vector<ll>> distance(n, vector<ll>(n, LIM));
for (ll i = 0; i < n; i++) {
    for (ll j = 0; j < graph[i].size(); j++) {
        ll node = graph[i][j];
        distance[i][node] = 1;
        distance[node][i] = 1;
    }
}
for (ll k = 0; k < n; k++) {
    for (ll i = 0; i < n; i++) {
        for (ll j = 0; j < n; j++) {
            if (distance[i][k] + distance[k][j] < distance[i][j]) {
                distance[i][j] = distance[i][k] + distance[k][j];
            }
        }
    }
}
```

### Minimum Spanning Tree

Prim's algorithm (lazy version)
```
using pll = pair<ll, ll>;
typedef struct comp {
    // first = node
    // second = weight
    bool operator() (pll& lhs, pll& rhs) {
        if (lhs.second != rhs.second) {
            return lhs.second > rhs.second;
        } else {
            return lhs.first > rhs.first;
        }
    }
} comp;

// mapping : adj list with element
// node : {other_node, weight}
// MST using Prim

priority_queue<pll, vector<pll>, comp> pq;
vector<int> visited(points.size(), 0);
visited[0] = 1;
for (auto& p : mapping[0]) {
    pq.push(p);
}
ll res = 0;
while (!pq.empty()) {
    auto p = pq.top();
    pq.pop();
    if (visited[p.first] == 1) continue;
    visited[p.first] = 1;
    res += p.second;
    for (auto& v : mapping[p.first]) {
        if (visited[v.first] == 0) {
            pq.push(v);
        }
    }
}
```

### Find Bridges in undirected graph

```
#define LENGTH 100010
int id;
map<int, vector<int>> mapping;  // adj list
int ids[LENGTH];
int lenId;

int lowLink[LENGTH];
int lowLinkId;

int visited[LENGTH];
int vId;

vector<vector<int>> bridges;
void dfs(int node, int parent) {
    ids[node] = id;
    lowLink[node] = id;
    id++;
    visited[node] = 1;
    for (int i : mapping[node]) {
        if (i == parent) continue;
        if (visited[i] == 0) {
            dfs(i, node);
            lowLink[node] = min(lowLink[node], lowLink[i]);
            if (ids[node] < lowLink[i]) {
                bridges.push_back(vector<int>{node, i});
            }
        } else {
            lowLink[node] = min(lowLink[node], ids[i]);
        }
    }
}

id = 0;
for (int i = 0; i < n; i++) {
    if (visited[i] == 0) {
        dfs(i, -1);
    }
}
```

### Find Eulerian Path
```

```
### Find Max Flow
#### Edmonds - Karp Algorithm
```
vector<vector<int>> capacity(101, vector<int>(101, 0));
vector<vector<int>> adjList(101);

int bfs(int s, int t, vector<int>& parent) {
    fill(parent.begin(), parent.end(), -1);
    parent[s] = -2;
    queue<pair<ll, ll>> toVisit;
    toVisit.push({s, 1000000000});
    while (!toVisit.empty()) {
        int curr = toVisit.front().first;
        int flow = toVisit.front().second;
        toVisit.pop();

        for (auto& next: adjList[curr]) {
            if (parent[next] == -1 && capacity[curr][next] > 0) {
                parent[next] = curr;
                int new_flow = min(capacity[curr][next], flow);
                if (next == t) {
                    return new_flow;
                }
                toVisit.push({next, new_flow}); 
            }
        }
    }
    return 0;
}

int maxFlow(int s, int t) {
    int flow = 0;
    vector<int> parent(N);
    int new_flow;

    new_flow = bfs(s, t, parent);
    while (new_flow > 0) {
        flow += new_flow;
        int curr = s;
        while (curr != s) {
            int prev = parent[curr];
            capacity[prev][curr] -= new_flow;
            capacity[curr][prev] += new_flow;
            curr = prev;
        }
        new_flow = bfs(s, t, parent);
    }
    return flow;
}
```