#include <cstdio>
#include <vector>
#include <utility>

#define MAX 10001
#define PAIR pair<int, int>

using namespace std;

bool IN[MAX], visit[MAX];
vector<int> v[MAX];

bool dfs(int cur) {
//    printf("[%d] ", cur);
    if (visit[cur])return false;
    visit[cur]=true;

    for (auto next : v[cur]) {
        if (!dfs(next))return false;
    }

    return true;
}

int main(void) {
    
    int T=0;
    register int x,y;
    while(true) {
        T++;

        for (register int i=0; i<MAX; ++i) {
            IN[i]=false;
            visit[i]=false;
            v[i].clear();
        }

        int N=0;
        while (true) {
            scanf("%d %d", &x, &y);
            
            if (x==-1 && y==-1) {
                N=-1;
                break;
            }
            else if (x==0 && y==0)break;

            N++;
            IN[y]=true;
            v[x].push_back(y);
        }
        if (N==-1)break;
        
        printf("Case %d is ", T);
        if (N==0) {
            printf("a tree.\n");
            continue;
        }
        
        vector<int> root;
        for (register int i=0; i<MAX && root.size()<2; ++i) {
            if (IN[i]==false && v[i].size()>0)root.push_back(i);
        }

        //printf("[ROOT SIZE] %d\n", root.size());

        if (root.size()!=1) {
            printf("not a tree.\n");
            continue;
        }
        
        bool TREE = dfs(root[0]);
        if (TREE) {
            printf("a tree.\n");
        }
        else {
            printf("not a tree.\n");
        }
    }
    

    return 0;
}
