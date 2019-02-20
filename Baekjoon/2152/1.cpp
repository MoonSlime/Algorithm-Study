#include <stdio.h>
#include <vector>

#define MAX 10001

using namespace std;

int N, M, S, T, vc=0, pos=0, answer=0;
int visit[MAX], finish[MAX], st[MAX];
vector<int> adj[MAX];
vector<vector<int> > SCC;

int dfs(int A) {
    if (visit[A] != 0)return visit[A];
    visit[A] = ++vc;
//    if (A == T)return MAX;
//    printf("push() = %d\n", A);
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
  //      printf("pop() = %d\n", top);
        newSCC.push_back(top);
        finish[top] = 1;
        if (top == A)break;
    }
    SCC.push_back(newSCC);

    if (visit[A] <= visit[T])answer += newSCC.size();
//    printf("%d\n", answer);

    return visit[A];
}

int main(void) {
    scanf("%d %d %d %d", &N, &M, &S, &T);

    int A,B;
    for (int i=0; i<M; ++i) {
        scanf("%d %d", &A, &B);
        adj[A].push_back(B);
    }

    //It is using SCC!!
    /**
    for (int i=0; i<N; ++i) {
        if (visit[i]==0)dfs(i);
    }
    **/

    //dfs(S)를 통해 T를 접근할수 없다면 이동할 수 없음.
    dfs(S);

    if (visit[T] == 0)
        printf("0\n");
    else
        printf("%d\n", answer);

    return 0;
}
