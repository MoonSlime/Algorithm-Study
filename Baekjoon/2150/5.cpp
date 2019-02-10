/**
 * SCC(Strongly Connected Component)이해를 위한 코드.
 *
 * 처음부터 천천히 다시해보자......(아직안했음2019/02/10)
 */
#include <stdio.h>
#include <vector>
#include <stack>
#include <algorithm>

#define MAX 10001

using namespace std;

int V, E, visit[MAX], vc=0;
vector<int> adj[MAX];//각 정점에 연결되어 있는 정점들. ex)adj[x]=y는 x->y를 의미.
vector<vector<int> > SCC;
stack<int> s;
bool finished[MAX];

bool less1(int a, int b) {
    return a < b;
}

bool less2(vector<int> a,vector<int> b) {
    return a[0] < b[0];
}

//scc를 구성하기 위한 dfs 함수.
int dfs(int x) {
    visit[x] = ++vc; 
    s.push(x);
    
    int ret=0;
    for (int i=0; i<adj[x].size(); ++i) {
        if (visit[adj[x][i]]==0) {
            ret = min(visit[x], dfs(adj[x][i]));
        }
        else if (!finished[visit[adj[x][i]]]) {
            ret = min(visit[x], visit[adj[x][i]]);
        }
    }

    if (ret != visit[x])return ret;

    vector<int> newSCC;
    while (s.top() != x) {
        int tmp = s.top();
        s.pop();
        newSCC.push_back(tmp);
        finished[tmp] = true;
    }
    newSCC.push_back(s.top());
    s.pop();

    sort(newSCC.begin(), newSCC.end(), less1);

    SCC.push_back(newSCC);
    return MAX;
}

int main(void) {
    scanf("%d %d", &V, &E);

    int x,y;
    for (int i=0; i<E; ++i) {
        scanf("%d %d", &x, &y);
        adj[x].push_back(y);
    }

    for (int i=1; i<=V; ++i) {
        if (visit[i] == 0)dfs(i);
    }

    sort(SCC.begin(), SCC.end(), less2);
    printf("%d\n", (int)SCC.size());
    for (int i=0; i<SCC.size(); ++i) {
        vector<int> cur = SCC[i];
        for (int j=0; j<cur.size(); ++j) {
            printf("%d ", cur[j]);
        }
        printf("-1\n");
    }

    return 0;
}
