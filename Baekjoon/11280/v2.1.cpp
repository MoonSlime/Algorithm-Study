/**
 * 만족하지 못하는 케이스 발견.
 *  2 4
 *  -2 -2
 *  -1 -2
 *  -1 -1
 *  1 2
 *
 *  문제 해결 :
 *  ret = min(visit[x], dfs(adj[x][i])) && ret = min(visit[x], visit[adj[x][i]) 를
 *  ret = min(ret, ~), min(ret, ~)으로 수정.
 *
 *  문제 발생 원인, ret에 이전의 값이 들어오더라도 이것을 저장하고 있지못하여 문제 발생.
 *  또한 if (ret != visit[x])return ret; 부분에서
 *  
 *  visit[x] = ret을 저장하고 있을 수 있도록 변경.
 *
 */

#include <cstdio>
#include <vector>
#include <functional>
#include <algorithm>

#define nomalization(x) x>0?2*x:(-2*x)+1
#define denomalization(x) x%2? -1 * (x/2) : x/2

using namespace std;

int N,M,size,pos,vc=0;
vector<int> visit,group,st;
vector<vector<int> > adj,SCC;

int dfs(int x) {
    st[pos++] = x;

    int ret = visit[x] = ++vc, len = adj[x].size();
    for (int i=0; i<adj[x].size(); ++i) {
        if (visit[adj[x][i]]==0) {
            ret = min(ret, dfs(adj[x][i]));
        }
        else if (group[adj[x][i]]==-1) {
            ret = min(ret, visit[adj[x][i]]);
        }
    }
    
    if (ret != visit[x]) {
        visit[x] = ret;
        return ret;
    }
    visit[x] = ret;

    vector<int> newV;
    int gn = SCC.size();
    while (true) {
        int top = st[--pos];
        newV.push_back(top);
        group[top] = gn;
        if (top == x)break;
    }
    SCC.push_back(newV);

    return ret;
}

int main(void) {
    scanf("%d %d", &N, &M);
    
    size = (N+1)*2;
    
    group.resize(size, -1);
    visit.resize(size);
    st.resize(size);
    adj.resize(size);
    
    int a,b;
    for (int i=0; i<M; ++i) {
        scanf("%d %d", &a, &b);
       
        adj[nomalization((-a))].push_back(nomalization(b));
        adj[nomalization((-b))].push_back(nomalization(a));
    }

    for (int i=2; i<size; ++i) {
        if (visit[i]==0)dfs(i);
    }

    for (int i=1; i<=N; ++i) {
        if (group[i*2]==group[i*2+1]) {
            printf("0\n");
            return 0;
        }
    }

    printf("1\n");
}

