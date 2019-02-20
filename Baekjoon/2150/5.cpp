/**
 * SCC(Strongly Connected Component)이해를 위한 코드.
 *
 * 처음부터 천천히 다시해보자......(아직안했음2019/02/10)
 *
 * 해결. 근데 이유는 아직 못찾음.
 */
#include <stdio.h>
#include <vector>
#include <algorithm>

#define MAX 10001

using namespace std;

int V, E, vc=0, pos=0;
int visit[MAX], scc[MAX], s[MAX];//s=stack
vector<int> adj[MAX];//각 정점에 연결되어 있는 정점들. ex)adj[x]=y는 x->y를 의미.
vector<vector<int> > SCC;

//scc를 구성하기 위한 dfs 함수.
int dfs(int x) {
    s[pos++]=x;

    int ret = visit[x] = ++vc;
    for (int y : adj[x]) {
        if (visit[y]==0) {
            ret = min(ret, dfs(y));
        }
        else if (!scc[y]) {
            ret = min(ret, visit[y]);
        }
    }

    if (ret != visit[x])return ret;

    int curSCC = SCC.size()+1;
    vector<int> newSCC;
    while (true) {
        int top = s[--pos];
        newSCC.push_back(top);
        scc[top]=curSCC;
        if (top == x)break;
    }
    sort(newSCC.begin(), newSCC.end());
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

    sort(SCC.begin(), SCC.end());
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
