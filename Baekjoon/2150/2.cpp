/**
 * SCC(Strongly Connected Component)이해를 위한 코드.
 */
#include <stdio.h>
#include <vector>
#include <set>

#define MAX 10001

using namespace std;

vector<int> adj[MAX];//각 정점에 연결되어 있는 정점들. ex)adj[x]=y는 x->y를 의미.
int V, E, visit[MAX], vc=0, scc[MAX];//vc = visit Count

//scc를 구성하기 위한 dfs 함수.
int dfs(int x) {
    if (visit[x]==vc) {
        if (scc[x]==0)scc[x] = x;
        return scc[x];
    }
    visit[x] = vc;
    
    int ret = 0;
    for (int i=0; i<adj[x].size(); ++i) {
        ret = dfs(adj[x][i]);
        if (ret)scc[x] = ret;
    }

    if (ret == x)return 0;
    return ret;
}

int main(void) {
    scanf("%d %d", &V, &E);

    int x,y;
    for (int i=0; i<E; ++i) {
        scanf("%d %d", &x, &y);
        adj[x].push_back(y);
    }

    for (int i=1; i<=V; ++i) {
        vc++;
        if (visit[i] == 0)dfs(i);
    }

    vector<int> answer, SCC[MAX];
    vc++;
    for (int i=1; i<=V; ++i) {
        int cur = scc[i];
        while (scc[cur]!=cur) {
            cur = scc[cur];
        }
        SCC[cur].push_back(i);

        if (visit[cur] != vc) {
            visit[cur] = vc;
            answer.push_back(cur);
        }
    }

    printf("%d\n", (int)answer.size());
    for (int i=0; i<answer.size(); ++i) {
        vector<int> cur = SCC[answer[i]];
        for (int j=0; j<cur.size(); ++j) {
            printf("%d ", cur[j]);
        }
        printf("-1\n");
    }



    return 0;
}
