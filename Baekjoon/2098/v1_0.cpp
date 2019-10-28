#include <cstdio>
#include <algorithm>

#define INF 999999999

using namespace std;

int N, D[17][1<<17], W[17][17], END;

void tsp(int cur, int n, int idx, int cost) {
    if (n==N-1) {
        if (W[cur][0]>0)D[0][END] = min(D[0][END],cost + W[cur][0]);
        return ;
    }
    if (D[cur][idx]!=0 && D[cur][idx]<=cost)return ;
    else D[cur][idx] = cost;

    for (int next=1; next<N; ++next) {
        if ((idx&(1<<next))>0 || W[cur][next]==0)continue;
        tsp(next, n+1, idx|(1<<next), cost+W[cur][next]);
    }
}

int main(void) {
    scanf("%d", &N);
    
    for (int i=0; i<N; ++i) {
        for (int j=0; j<N; ++j) {
            scanf("%d", &W[i][j]);
        }
    }

    END = (1<<N) - 1;
    D[0][END] = INF;
    tsp(0, 0, 0, 0);
    
    if(D[0][END]>0)printf("%d\n", D[0][END]);

    return 0;
}
