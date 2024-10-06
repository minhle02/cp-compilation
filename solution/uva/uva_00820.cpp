#include <bits/stdc++.h>
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

vector<vector<int>> capacity(101, vector<int>(101, 0));
vector<vector<int>> adjList(101);
int N;

int source, sink;
int from, to, cost;

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

int main() {
#ifdef LOCALONLY
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(0);
    int testcase = 1;
    while (cin >> N && N != 0) {
        capacity.resize(N);
        for (auto& v : capacity) {
            v.resize(N);
            fill(v.begin(), v.end(), 0);
        }
        adjList.resize(N);
        fill(adjList.begin(), adjList.end(), vi());

        cin >> source >> sink;
        source--;
        sink--;

        int numLine;
        cin >> numLine;
        FOR0(i, numLine) {
            cin >> from >> to >> cost;
            from--;
            to--;
            capacity[from][to] += cost;
            capacity[to][from] += cost;
            adjList[from].push_back(to);
            adjList[to].push_back(from);
        }
        printf("Network %d\n", testcase);
        printf("The bandwidth is %d.\n\n", maxFlow(source, sink));
        testcase++;
    }
    return 0;
}