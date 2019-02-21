/**
 * 문제풀이는 되는것 같으나, 런타임 오류 발생. 
 *
 * 예측 이유 : 배열의 인덱스.
 *
 * 해결 : v1.2
 */
#include <cstdio>
#include <vector>

#define MAX 100001

using namespace std;

int N,M,pos,vc=0;
int state[MAX];
vector<int> visit, group, st;
vector<vector<int> > adj, SCC, room;

int NOT(int x) {
    return x+N;
}

int scc(int x) {
    st[pos++] = x;

    int ret = visit[x] = ++vc;
    for (int next : adj[x]) {
        if (visit[next]==0) {
            ret = min(ret, scc(next));
        }
        else if (group[next]==-1) {
            ret = min(ret, visit[next]);
        }
    }

    if (ret != visit[x]) {
        visit[x] = ret;
        return ret;
    }

    int gn = SCC.size();
    SCC.push_back(vector<int>());
    while(true) {
        int top = st[--pos];
        SCC[gn].push_back(top);
        group[top]=gn;
        if (top == x)break;
    }

    return ret;
}

int main(void) {
    scanf("%d %d", &N, &M);

    visit.resize((N+1)*2);
    group.resize((N+1)*2, -1);
    st.resize((N+1)*4);
    adj.resize((N+1)*2);
    room.resize((N+1));

    for (int i=1; i<=N; ++i) {
        scanf("%d", &state[i]);
    }

    for (int i=1; i<=M; ++i) {
        int n, tmp;
        scanf("%d", &n);
        while (n--) {
            scanf("%d", &tmp);
            room[tmp].push_back(i);
        }
    }

    for (int i=1; i<=N; ++i) {
        int btn1=room[i][0];
        int btn2=room[i][1];
        if (state[i]==0) {
            adj[btn1].push_back(NOT(btn2));
            adj[btn2].push_back(NOT(btn1));
            adj[NOT(btn1)].push_back(btn2);
            adj[NOT(btn2)].push_back(btn1);
        }
        else if (state[i]==1) {
            adj[btn1].push_back(btn2);
            adj[btn2].push_back(btn1);
            adj[NOT(btn1)].push_back(NOT(btn2));
            adj[NOT(btn2)].push_back(NOT(btn1));
        }
    }

    for (int i=1; i<=N; ++i) {
        if (visit[i]==0)scc(i);
        if (visit[NOT(i)]==0)scc(NOT(i));
    }

    /**
    printf("===SCC====\n");
    for (int i=0; i<SCC.size(); ++i) {
        for (int next : SCC[i]) {
            printf("%d ", next);
        }
        printf("\n");
    }
    printf("===END====\n");
    **/

    for (int i=1; i<=N; ++i) {
        if (group[i] == group[NOT(i)]) {
            return !printf("0\n");
        }
    }

    return !printf("1\n");
}
