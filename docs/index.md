# Algorithm 

<!-- TOC start (generated with https://github.com/derlin/bitdowntoc) -->

- [Algorithm](#algorithm)
  - [Sparse Table](#sparse-table)
  - [Graphs](#graphs)
    - [BF Shortest Path](#bf-shortest-path)
    - [Djikstra Shortest Path](#djikstra-shortest-path)

<!-- TOC end -->

<!-- TOC --><a name="sparse-table"></a>
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

<!-- TOC --><a name="graphs"></a>
## Graphs

<!-- TOC --><a name="bf-shortest-path"></a>
### BF Shortest Path

- Change LIM
- Change number in for loop
- Change mask
- Change MOVES

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

<!-- TOC --><a name="djikstra-shortest-path"></a>
### Djikstra Shortest Path