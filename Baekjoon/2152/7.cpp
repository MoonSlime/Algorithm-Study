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

int N, M, S, T, vc=0;
vector<int> visit, st, group;
vector<vector<int> > adj, SCC;

int dfs(int A) {
    if (visit[A] != 0)return visit[A];
    visit[A] = ++vc;
    st.push_back(A);

    int ret=visit[A];
    vector<int> cur = adj[A];
    for (int i=0; i<cur.size(); ++i) {
        if (visit[cur[i]]==0)
            ret = min(ret, dfs(cur[i]));
        else if (group[cur[i]]==-1)
            ret = min(ret, visit[cur[i]]);
    }


    if (visit[A] != ret)return ret;

    int top;
    vector<int> newSCC;
    while (true) {
        top = st.back();
        st.pop_back();
        newSCC.push_back(top);
        group[top] = SCC.size();
        if (top == A)break;
    }
    SCC.push_back(newSCC);

    return visit[A];
}

vector<vector<int> > dag;

//https://new93helloworld.tistory.com/182 보면 좋을듯.
void getDAG(int cur) {
    vector<int> CUR=SCC[cur],NEXT;
    for (int next=0; next<cur; ++next) {
        NEXT = SCC[next];
        bool check = false;
        for (int i=0; i<NEXT.size(); ++i) {
            for (int j=0; j<CUR.size(); ++j) {
                for (int k=0; k<adj[CUR[j]].size(); ++k) {
                    if (adj[CUR[j]][k] == NEXT[i]) {
                        dag[cur][next] = 1;
                        getDAG(next);
                        check = true;
                        break;
                    }
                }
                if (check)break;
            }
            if (check)break;
        }
    }
}

//SCC[cur]->SCC[next]의 경로를 찾아, 지나가는 SCC그룹의 size()를 더해감.
int dfs2(int cur) {
    if (cur == group[T])return SCC[cur].size();

    int ret = -1 * MAX;

    //다음 이동할 수 있는 경로는 cur 보다 이전에 생성된 SCC그룹이다.
    for (int next=0; next<cur; ++next) {
        if (dag[cur][next]) {
            ret = max(ret, (int)SCC[cur].size() + dfs2(next));
        }
    }

    return ret<0 ? -1*MAX : ret;
}

int main(void) {
    scanf("%d %d %d %d", &N, &M, &S, &T);

    for (int i=0; i<=N; ++i) {
        vector<int> newV;
        adj.push_back(newV);
    }
    visit.resize(N+1, 0);
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

    for (int i=0; i<=SCC.size(); ++i) {
        vector<int> newV;
        newV.resize(SCC.size()+1, 0);
        dag.push_back(newV);
    }
    getDAG(group[S]);
    printf("%d\n", dfs2(group[S]));
    
    return 0;
}
