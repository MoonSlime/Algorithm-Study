#include <cstdio>
#include <vector>
#include <functional>
#include <algorithm>

#define nomalization(x) x>0?2*x:(-2*x)+1
#define denomalization(x) x/2

using namespace std;

int N,M,size,pos,vc=0;
vector<int> visit,group,st;
vector<vector<int> > adj,SCC;

int dfs(int x) {
    //printf("dfs(%d)\n", x);
    st[pos++] = x;

    int ret = visit[x] = ++vc, len = adj[x].size();
    for (int i=0; i<len; ++i) {
        if (visit[adj[x][i]]==0) {
            ret = min(visit[x], dfs(adj[x][i]));
        }
        else if (group[adj[x][i]]==-1) {
            ret = min(visit[x], visit[adj[x][i]]);
        }
    }

    if (ret != visit[x])return ret;

    int gn = SCC.size();
    vector<int> newV;
    SCC.push_back(newV);
    while (true) {
        int top = st[--pos];
        SCC[gn].push_back(top);
        group[top] = gn;
        if (top == x)break;
    }

    sort(SCC[gn].begin(), SCC[gn].end(), less<int>());

    return ret;
}

int main(void) {
    scanf("%d %d", &N, &M);
    
    size = (N+1)*2;

    visit.resize(size);
    group.resize(size, -1);
    st.resize(size);
    adj.resize(size);

    int a,b;
    for (int i=0; i<M; ++i) {
        scanf("%d %d", &a, &b);
        adj[nomalization(-1 * a)].push_back(nomalization(b));
        adj[nomalization(-1 * b)].push_back(nomalization(a));
    }

    for (int i=2; i<size; ++i) {
        if (visit[i]==0)dfs(i);
    }

    /**
    for (int i=0; i<SCC.size(); ++i) {
        for (int j=0; j<SCC[i].size(); ++j) {
            printf("%d ", SCC[i][j]);
        }
        printf("\n");
    }
    **/

    /**
    for (int i=0; i<SCC.size(); ++i) {
        int len = SCC[i].size()-1;
        for (int j=0; j<len; ++j) {
            if (denomalization(SCC[i][j]) == denomalization(SCC[i][j+1])) {
                printf("0\n");
                return 0;
            }
        }
    }
    **/

    for (int i=1; i<=N; ++i) {
        if (group[nomalization(i)] == group[nomalization(-1*i)]) {
            if (group[nomalization(i)]==-1)continue;
            printf("0\n");
            return 0;
        }
    }

    printf("1\n");
    return 0;
}

