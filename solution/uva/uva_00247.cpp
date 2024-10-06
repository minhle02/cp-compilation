#include <bits/stdc++.h>
#include <cstdio>
using namespace std;

/******* Set up *******/
#define FOR(i, L ,R) for (int i = L; i < R; i++)
#define FOR0(i, N) for (int i = 0; i < N; i++)
#define endl "\n"
using ll=long long;
using vi = vector<int>;
using vii = vector<vector<int>>;
/**********************/

ll n, m;
char name1[30], name2[30];
ll TC;
ll ID;
map<string, vector<string>> adjList;
map<string, bool> onStack;
map<string, bool> visited;
map<string, int> id;
map<string, int> lowLink;

void dfs(stack<string>& toVisit, string curr, vector<string>& updated) {
    toVisit.push(curr);
    onStack[curr] = true;
    id[curr] = ID;
    lowLink[curr] = ID;
    ID += 1;
    for (auto& neighbor : adjList[curr]) {
        if (id[neighbor] == 0) { // Not visited
            dfs(toVisit, neighbor, updated);
        }
        if (onStack[neighbor]) {
            lowLink[curr] = min(lowLink[curr], lowLink[neighbor]);
        }
    }

    if (id[curr] == lowLink[curr]) {
        // string temp = toVisit.top();
        while (!toVisit.empty()) {
            string temp = toVisit.top();
            toVisit.pop();
            updated.push_back(temp);
            onStack[temp] = false;
            lowLink[temp] = min(lowLink[temp], id[curr]);
            if (temp == curr) {
                printf("%s\n", temp.c_str());
                break;
            } else {
                printf("%s, ", temp.c_str());
            }
        }
    }
}

void solve() {
    printf("Calling circles for data set %lld:\n", TC);
    ID = 1;
    for (auto& p : adjList) {
        onStack[p.first] = false;
        visited[p.first] = false;
        id[p.first] = 0;
        lowLink[p.first] = 0; 
    }
    stack<string> toVisit;
    for (auto& p : adjList) {
        if (id[p.first] == 0) {
            vector<string> updated;
            dfs(toVisit, p.first, updated);
        }
    }

}

int main() {

#ifdef LOCALONLY
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
    
    scanf("%lld %lld", &n, &m);
    TC = 1;
    while (n != 0 ||m != 0) {
        adjList.clear();
        onStack.clear();
        id.clear();
        lowLink.clear();
        int idx = 0;
        FOR0(i, m) {
            scanf("%s %s", &name1[0], &name2[0]);
            string str1{name1}, str2{name2};
            if (find(adjList[str1].begin(), adjList[str1].end(), str2) != adjList[str1].end()) {
                continue;
            }
            adjList[str1].push_back(str2);
            if (adjList.find(str2) == adjList.end()) {
                adjList[str2] = vector<string>{};
            }
        }
        solve();
        scanf("%lld %lld", &n, &m);
        TC++;
        if (n != 0 || m != 0) {
            printf("\n");
        }
    }
    return 0;
}