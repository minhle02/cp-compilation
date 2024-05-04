# Snippet

## Quick type

```
#define FOR(i, L ,R) for (int i = L; i < R; i++)
#define FOR0(i, N) for (int i = 0; i < N; i++)
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
void Print_Arr(int64_t* _n, int _l) {
    for (int i = 0; i < _l; i++) {
        cout << _n[i] << " ";
    }
    cout << endl;
}
int currTC = 0;
```

# Algorithm - Basic

## Sparse Table
```
#define NC 250010
#define MAX_EXPO 20
#define FOR(i, L ,R) for (int i = L; i < R; i++)
#define FOR0(i, N) for (int i = 0; i < N; i++)

int64_t sparse_table[MAX_EXPO][NC];

void gen_sparse_table() {
    for (int i = 0; i < cc_idx; i++){
        sparse_table[0][i] = connected_component[i];
    }

    int expo = floor(log2(cc_idx)) + 1;
    int e;

    for (int i = 1; i < expo; i++) {
        for (int j = 0; j + (1 << i) <= cc_idx; j++) {
            sparse_table[i][j] = lcm(sparse_table[i - 1][j], sparse_table[i - 1][j + (1 << (i - 1))]);
        }
    }
}

int lcm_query(int l, int r) {
    if (r < l) {
        return 1;
    }
    int len = r - l + 1;
    int e = floor(log2(len));
    return lcm(sparse_table[e][l], sparse_table[e][r - (1 << e) + 1]);
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
// graph: edge list
n = graph.size();
vector<vector<int>> distance(n, vector<int>(n, LIM));
for (int i = 0; i < n; i++) {
    for (int j = 0; j < graph[i].size(); j++) {
        int node = graph[i][j];
        distance[i][node] = 1;
        distance[node][i] = 1;
    }
}
for (int k = 0; k < n; k++) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (distance[i][k] + distance[k][j] < distance[i][j]) {
                distance[i][j] = distance[i][k] + distance[k][j];
            }
        }
    }
}
```

### Minimum Spanning Tree
```
using pii = pair<int, int>;
typedef struct comp {
    // first = node
    // second = weight
    bool operator() (pii& lhs, pii& rhs) {
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

priority_queue<pii, vector<pii>, comp> pq;
vector<int> visited(points.size(), 0);
visited[0] = 1;
for (auto& p : mapping[0]) {
    pq.push(p);
}
int res = 0;
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