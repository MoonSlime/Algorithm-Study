/**
 * dfs를 통해 SCC의 집합을 구성하고,
 * 구성한 SCC들 간의 이동 경로를 예측한다.
 *
 * 결과 : 시간초과!!!!!!!!!
 * 이유 분석 : dfs2의 탐색시간이 오래걸릴 것이다.
 * 해결 방법 : SCC간의 연결요소들을 초기화후, 저장하여 사용하면 되지만, 
 * 우선 SCC의 스택상황에대해 이해한 후, 애초에 걸리는 시간을 줄여보자.
 */

//X->Y nono
//Y->X yesyes

#include <stdio.h>
#include <vector>
#include <algorithm>

#define MAX 10001

using namespace std;

int N, M, S, T, vc=0, pos=0;
int visit[MAX], st[MAX];
vector<int> adj[MAX], group;
vector<vector<int> > SCC;

int dfs(int A) {
    if (visit[A] != 0)return visit[A];
    visit[A] = ++vc;
    st[pos++]=A;

    int ret=visit[A];
    vector<int> cur = adj[A];
    for (int i=0; i<cur.size(); ++i) {
        if (visit[cur[i]]==0)
            ret = min(ret, dfs(cur[i]));
        else if (group[cur[i]]==-1)
            ret = min(ret, visit[cur[i]]);
    }

//    printf("[%d, %d]\n", visit[A], ret);

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

//SCC[cur]->SCC[next]의 경로를 찾아, 지나가는 SCC그룹의 size()를 더해감.
int dfs2(int cur) {
    if (cur == group[T])return SCC[cur].size();

    int ret = -1 * MAX;

    vector<int> CUR=SCC[cur],NEXT;

    for (int next=0; next<SCC.size(); ++next) {
        if (next == cur)continue;

        NEXT = SCC[next];
        for (int i=0; i<NEXT.size(); ++i) {
            for (int j=0; j<CUR.size(); ++j) {
                for (int k=0; k<adj[CUR[j]].size(); ++k) {
                    if (adj[CUR[j]][k] == NEXT[i]) {
                        int tmp = dfs2(group[NEXT[i]]);//==dfs2(next)
                        ret = max(ret, (int)SCC[cur].size() + tmp);
                    }
                }
            }
        }
    }

    return ret<0 ? -1*MAX : ret;
}

int main(void) {
    scanf("%d %d %d %d", &N, &M, &S, &T);

    group.resize(MAX, -1);

//    printf("%d %d %d\n", group[0],group[1], group[2]);

    int A,B;
    for (int i=0; i<M; ++i) {
        scanf("%d %d", &A, &B);
        adj[A].push_back(B);
    }

    //dfs(S)를 통해 T를 접근할수 없다면, S->T를 이동할 수 없음.
    dfs(S);


    if (visit[T] == 0) {//같은말인데 그냥 두개다 확인 ㅎ..
        printf("0\n");
        return 0;
    }

    ++vc;
    int ret = dfs2(group[S]);
    printf("%d\n", ret);
    
    return 0;
}
