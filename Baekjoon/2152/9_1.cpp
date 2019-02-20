/**
 * dfs를 통해 SCC의 집합을 구성하고,
 * 구성한 SCC들 간의 이동 경로를 예측한다.
 *
 * 결과 : 메모리초과... ㅋㅋ
 * 이유 분석 : 사용하는 배열이 너무 많아서 ㅋㅋㅋㅋ
 * 해결 방법: 동적으로 배열을 할당해서 사용하자.(vector)
 */


#include <stdio.h>
#include <vector>
#include <algorithm>

#define MAX 10001

using namespace std;

int N, M, S, T, vc=0,pos=0, visit[MAX], st[MAX];
vector<int> group, adj[MAX], dag[MAX];
vector<vector<int> > SCC;

int dfs(int A) {
    visit[A] = ++vc;
    st[pos++]=A;

    vector<int> cur = adj[A];
    int ret=visit[A], cur_len = cur.size();
    for (int i=0; i<cur_len; ++i) {
        if (visit[cur[i]]==0)
            ret = min(ret, dfs(cur[i]));
        else if (group[cur[i]]==-1)
            ret = min(ret, visit[cur[i]]);
    }

    if (visit[A] != ret)return ret;

    int top, gn=SCC.size();
    vector<int> newSCC;
    SCC.push_back(newSCC);
    while (true) {
        top = st[--pos];
        SCC[gn].push_back(top);
        group[top] = gn;
        if (top == A)break;
    }

    return visit[A];
}

//adj[cur][next]
void getDAG2(int cur) {
    for (int i=0; i<adj[cur].size(); ++i) {
        if (group[cur] == group[adj[i]])continue;
        dag[group[cur]].push_back(group[adj[i]]);
        getDAG2(i);
    }
}

void getDAG() {
    for (int i=1; i<=N; ++i) {
        if (visit[i]==0)continue;
        ++vc;
        for (auto next : adj[i]) {
            int c=group[i],n=group[next];
            if (c == n || visit[n] == vc)continue;
            visit[n]=vc;
            dag[c].push_back(n);
        }
    }

}

//SCC[cur]->SCC[next]의 경로를 찾아, 지나가는 SCC그룹의 size()를 더해감.
int dfs2(int cur) {
    if (cur == group[T])return SCC[cur].size();

    int ret = -1 * MAX;

    int dag_len = dag[cur].size();
    for (int i=0; i<dag_len; ++i) {
        ret = max(ret, (int)SCC[cur].size() + dfs2(dag[cur][i]));
    }

    return ret<0 ? -1*MAX : ret;
}

int main(void) {
    scanf("%d %d %d %d", &N, &M, &S, &T);
    
    group.resize(N+1, -1);

    int A,B;
    for (int i=0; i<M; ++i) {
        scanf("%d %d", &A, &B);
        adj[A].push_back(B);
    }

    //dfs(S)를 통해 T를 접근할수 없다면, S->T를 이동할 수 없음.
    dfs(S);

    if (visit[T] == 0) {
        printf("0\n");
        return 0;
    }

    getDAG();
    printf("%d\n", dfs2(group[S]));
    
    return 0;
}
