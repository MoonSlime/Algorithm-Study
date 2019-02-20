/**
 * dfs를 통해 SCC의 집합을 구성하고,
 * 구성한 SCC들 간의 이동 경로를 예측한다.
 *
 * ex) A,B,C라는 SCC가 있을경우 (A에 시작지점, C에 도착지점이 존재.)
 * A->B->C
 *
 * 1.
 * cur = C;
 * A->cur;B->cur; check.
 * 
 * answer += B.size();
 *
 * 2.
 * cur = B;
 * A->cur;
 *
 * answer += A.size();
 *
 * if (A==시작지점)break;
 *
 * 결과 : 틀림...
 * 이유 분석 : cur로 갈수있는 길이 여러가지 있을경우를 체크하지못함.
 * 해결 방법 : 재귀함수를 이용한 backtracking 방법이 좋을거 같음.
 */

#include <stdio.h>
#include <vector>

#define MAX 10001

using namespace std;

int N, M, S, T, vc=0, pos=0, scc_of_t=-1;
int visit[MAX], finish[MAX], st[MAX];
vector<int> adj[MAX];
vector<vector<int> > SCC;

int dfs(int A) {
    if (visit[A] != 0)return visit[A];
    visit[A] = ++vc;
//    if (A == T)return MAX;
    st[pos++]=A;

    int ret=visit[A];
    vector<int> cur = adj[A];
    for (int i=0; i<cur.size(); ++i) {
        if (visit[cur[i]]==0)
            ret = min(ret, dfs(cur[i]));
        else if (!finish[cur[i]])
            ret = min(ret, visit[cur[i]]);
    }
    //visit[A] = ret;
    if (visit[A] != ret)return ret;

    int top;
    vector<int> newSCC;
    while (true) {
        top = st[--pos];
        newSCC.push_back(top);
        finish[top] = 1;
        if (top == T)scc_of_t = SCC.size();
        if (top == A)break;
    }
    SCC.push_back(newSCC);
//    if (visit[A] <= visit[T])answer += newSCC.size();

    return visit[A];
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
    int cur = scc_of_t, answer=SCC[cur].size();
    bool check; 
    vector<int> X,Y;
    while (true) {
//        printf("CUR = %d\n", cur);
        Y = SCC[cur];
        visit[cur] = vc;
        check = false;
        for (int i=0; i<SCC.size(); ++i) {
            if (visit[i]==vc)continue;

            X = SCC[i];
            for (int j=0; j<X.size(); ++j) {
                for (int k=0; k<Y.size(); ++k) {
                    for (int l=0; l<adj[X[j]].size(); ++l) {
                        if (adj[X[j]][l] == Y[k]) {
                            check = true;
                            break;
                        }
                    }
                    if (check)break;
                }
                if (check)break;
            }
            if (check) {
                answer += SCC[i].size();
                cur = i;
                break;
            }
        }
        if (!check)break;
    }

    printf("%d\n", answer);

    return 0;
}
