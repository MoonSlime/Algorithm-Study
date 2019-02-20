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

//SCC[y]로 갈수있는 SCC[x]의 최대 크기.
int canGo(int y) {
    int ret = SCC[y].size();
    if (y==scc_of_s)return ret;

    visit[y]=vc;
    bool check, check2=false;
    vector<int> X, Y = SCC[y];
    for (int x=0; x<SCC.size(); ++x) {
        if (visit[x]==vc)continue;
        X = SCC[x];

        check = false;
        for (int i=0; i<X.size(); ++i) {
            for (int j=0; j<Y.size(); ++j) {
                for (int k=0; k<adj[X[i]].size(); ++k) {
                    if (adj[X[i]][k]==Y[j]) {
                        check = true;
                        check2= true;
                        break;
                    }
                }
            }
        }
        if (check)ret = max(ret, ret + canGo(x));
    }
    visit[y] = 0;

    return check2 ? ret : -1 * MAX;
}

int main(void) {
    scanf("%d %d %d %d", &N, &M, &S, &T);

    int A,B;
    for (int i=0; i<M; ++i) {
        scanf("%d %d", &A, &B);
        adj[A].push_back(B);
    }

    //dfs(S)를 통해 T를 접근할수 없다면 이동할 수 없음.
    dfs(S);

    if (visit[T] == 0 || scc_of_t == -1) {//같은말인데 그냥 두개다 확인 ㅎ..
        printf("0\n");
        return 0;
    }

    ++vc;
    int ret = canGo(scc_of_t);
    printf("%d\n", ret);
    
    return 0;
}
