# Algorithm

## Sparse Table

## Graphs

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

### Djikstra Shortest Path