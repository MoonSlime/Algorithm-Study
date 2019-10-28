#include <cstdio>
#include <algorithm>

#define INF 999999999

using namespace std;

int N, D[17][1<<17], W[17][17], END;

int tsp(int cur, int idx) {
    if (idx == END) {
        if (W[cur][0]==0)return INF;
        else return W[cur][0];
    }

    if (D[cur][idx]>0)return D[cur][idx];

    D[cur][idx] = INF;
    for (int next=1; next<N; ++next) {
        if ((idx&(1<<next))>0 || W[cur][next]==0)continue;
        D[cur][idx] = min(D[cur][idx], tsp(next, idx|(1<<next))+W[cur][next]);
    }

    return D[cur][idx];
}

int main(void) {
    scanf("%d", &N);
    
    for (int i=0; i<N; ++i) {
        for (int j=0; j<N; ++j) {
            scanf("%d", &W[i][j]);
        }
    }

    END = (1<<N) - 1;
    int answer = tsp(0, 1);
    
    if (answer>0)printf("%d\n", answer);

    return 0;
}
