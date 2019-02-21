#include <cstdio>
#include <vector>

#define MAX 100001

using namespace std;

int N,M,pos,vc=2;
vector<int> visit, group, st;
vector<vector<int> > adj, SCC, room;

int NOT(int x) {
    return x+N;
}

int scc(int x) {
    st[pos++] = x;

    int ret = visit[x] = ++vc;
    for (int i=0; i<adj[x].size(); ++i) {
        if (visit[adj[x][i]]==0) {
            ret = min(ret, scc(adj[x][i]));
        }
        else if (group[adj[x][i]]==-1) {
            ret = min(ret, visit[adj[x][i]]);
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

    if (N>1000)return 0;

    visit.resize((N+1)*2);
    adj.resize((N+1)*2);
    room.resize(N+1);

    //state -> visit.
    for (int i=1; i<=N; ++i) {
        scanf("%d", &visit[i]);
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
        if (visit[i]==0) {
            adj[btn1].push_back(NOT(btn2));
            adj[btn2].push_back(NOT(btn1));
            adj[NOT(btn1)].push_back(btn2);
            adj[NOT(btn2)].push_back(btn1);
        }
        else if (visit[i]==1) {
            adj[btn1].push_back(btn2);
            adj[btn2].push_back(btn1);
            adj[NOT(btn1)].push_back(NOT(btn2));
            adj[NOT(btn2)].push_back(NOT(btn1));
        }
    }

    visit.erase(visit.begin(), visit.end());
    visit.clear();
    visit.resize((N+1)*2, 0);

    room.erase(room.begin(), room.end());
    room.clear();


    group.resize((N+1)*2, -1);
    st.resize((N+1)*2);
    
    for (int i=1; i<=N; ++i) {
        if (visit[i]==0)scc(i);
        if (visit[NOT(i)]==0)scc(NOT(i));
    }

    for (int i=1; i<=N; ++i) {
        if (group[i] == group[NOT(i)]) {
            return !printf("0\n");
        }
    }

    return !printf("1\n");
}
