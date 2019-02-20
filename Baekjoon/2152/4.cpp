/**
 * dfs를 통해 SCC의 집합을 구성하고,
 * 구성한 SCC들 간의 이동 경로를 예측한다.
 * 
 * 도착지점 T가 속한 SCC로 갈 수 있는 SCC집합 간의 경로들을 모두 탐색한다.
 *
 * 결과 : 틀림...
 * 이유 분석 : 로직이 틀린것같다.
 * 해결 방법 : 도착지점으로가 아닌, 시작지점 부터의 DFS Spanning Tree를 하면 될 것 같다.
 */

#include <stdio.h>
#include <vector>
#include <algorithm>

#define MAX 10001

using namespace std;

int N, M, S, T, vc=0, pos=0, scc_of_s=-1, scc_of_t=-1;
int visit[MAX], finish[MAX], st[MAX];
vector<int> adj[MAX];
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
        else if (!finish[cur[i]])
            ret = min(ret, visit[cur[i]]);
    }
    if (visit[A] != ret)return ret;

    int top;
    vector<int> newSCC;
    while (true) {
        top = st[--pos];
        newSCC.push_back(top);
        finish[top] = 1;
        if (top == S)scc_of_s = SCC.size();
        if (top == T)scc_of_t = SCC.size();
        if (top == A)break;
    }
    SCC.push_back(newSCC);
//    if (visit[A] <= visit[T])answer += newSCC.size();

    return visit[A];
}

//SCC[x]->SCC[y]의 경로를 찾아, 지나가는 SCC그룹의 size()를 더해감.
int dfs2(int x) {
    if (x==scc_of_t)return SCC[x].size();
    
    int ret = -1 * MAX;

    visit[x] = vc;
    vector<int> X=SCC[x],Y;
    for (int y=0; y<SCC.size(); ++y) {
        if (x==y)continue;
//        if (visit[y]==vc)continue;

        Y = SCC[y];
        int i,j,k;
        for (i=0; i<X.size(); ++i) {
            for (j=0; j<Y.size(); ++j) {
                for (k=0; k<adj[X[i]].size(); ++k) {
                    if (adj[X[i]][k] == Y[j]) {
                        int tmp = dfs2(y);
                        if (tmp==-1) {
                            i = X.size();
                            break;
                        }
                        ret = max(ret, (int)SCC[x].size() + tmp);
                        break;
                    }
                }
                if (k!=adj[X[i]].size())break;
            }
            if (j!=Y.size())break;
        }
        if (i!=X.size())break;
    }
    visit[x] = 0;

    return ret;
}

int main(void) {
    scanf("%d %d %d %d", &N, &M, &S, &T);

    int A,B;
    for (int i=0; i<M; ++i) {
        scanf("%d %d", &A, &B);
        adj[A].push_back(B);
    }

    //dfs(S)를 통해 T를 접근할수 없다면, S->T를 이동할 수 없음.
    dfs(S);
/**
    for (int i=0; i<SCC.size(); ++i) {
        for (int j=0; j<SCC[i].size(); ++j) {
            printf("%d ",SCC[i][j]);
        }
        printf("\n");
    }
**/
    if (visit[T] == 0 || scc_of_t == -1) {//같은말인데 그냥 두개다 확인 ㅎ..
        printf("0\n");
        return 0;
    }

    ++vc;
    
    int ret = dfs2(scc_of_s);
    printf("%d\n", ret);
    
    return 0;
}
