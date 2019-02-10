/**
 * SCC(Strongly Connected Component)이해를 위한 코드.
 *
 * Stack을 이용한 구현1.
 * 틀린 답. 이유는 visit변수 하나로는 vc의체크는 가능하지만, scc형성이 완료되었는지 알 수가 없어서??
 */
#include <stdio.h>
#include <vector>
#include <stack>
#include <algorithm>

#define MAX 10001

using namespace std;

int V, E, scc[MAX], visit[MAX], vc=0;
vector<int> adj[MAX];//각 정점에 연결되어 있는 정점들. ex)adj[x]=y는 x->y를 의미.
vector<vector<int> > SCC;
stack<int> s;

bool less1(int a, int b) {
    return a < b;
}

bool less2(vector<int> a,vector<int> b) {
    return a[0] < b[0];
}

//scc를 구성하기 위한 dfs 함수.
int dfs(int x) {
    if (visit[x] != 0)return visit[x];
    int cur = ++vc;

    visit[x] = cur;
    s.push(x);
    
    for (int i=0; i<adj[x].size(); ++i) {
        visit[x] = min(visit[x], dfs(adj[x][i]));
    }

    if (cur != visit[x])return visit[x];

    vector<int> newSCC;
    while (s.top() != x) {
        newSCC.push_back(s.top());
        s.pop();
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
