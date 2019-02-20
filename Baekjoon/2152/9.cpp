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
    if (visit[A] != 0)return visit[A];
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

    int top;
    vector<int> newSCC;
    while (true) {
        top = st[--pos];
        newSCC.push_back(top);
        group[top] = SCC.size();
        if (top == A)break;
    }
    SCC.push_back(newSCC);

    return visit[A];
}


void getDAG2() {
    for (int i=1; i<=N; ++i) {
        ++vc;
        for (auto next : adj[i]) {
            if (group[i]==-1 || group[next]==-1)continue;
            if (group[i] == group[next] || visit[group[next]] == vc)continue;
            visit[group[next]]=vc;
            dag[group[i]].push_back(group[next]);
        }
    }

}

//SCC[cur]->SCC[next]의 경로를 찾아, 지나가는 SCC그룹의 size()를 더해감.
int dfs2(int cur) {
    if (cur == group[T])return SCC[cur].size();

    int ret = -1 * MAX;

    int dag_len = dag[cur].size();
    //다음 이동할 수 있는 경로는 cur 보다 이전에 생성된 SCC그룹이다.
    for (int next=0; next<cur; ++next) {
        for (int i=0; i<dag_len; ++i) {
            if (dag[cur][i] == next) {
                ret = max(ret, (int)SCC[cur].size() + dfs2(next));
                break;
            }
        }
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

    int scc_len=SCC.size();;
    getDAG2();
    //getDAG(group[S]);
    printf("%d\n", dfs2(group[S]));
    
    return 0;
}
