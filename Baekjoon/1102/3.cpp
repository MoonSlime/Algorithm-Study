#include <cstdio>
#include <cmath>
#include <algorithm>

#define INF 100000

using namespace std;

char str[17];
int N, P, cost[16][16], D[(int)(1<<16)];
//D[j] == j 상태일 때의 최소 값. 

int tsp(int stat, int p) {
    if (p >= P) {
        //return D[cur][stat];// == return 0;
        return 0;// == return 0;
    }
    else if (D[stat]>0)return D[stat];
    
    D[stat] = INF;
    for (int i=0; i<N; ++i) {
        if ((stat & (1<<i))==0)continue;
        for (int j=0; j<N; ++j) {
            if (i==j)continue;
            if ((stat&(1<<j))==0 && cost[i][j]>=0) {
                D[stat] = min(D[stat], tsp(stat|(1<<j), p+1) + cost[i][j]);
            }
        }
    }
    
    return D[stat];
}

int main(void) {
    scanf("%d", &N);

    for (int i=0; i<N; ++i) {
        for (int j=0; j<N; ++j) {
            scanf("%d", &cost[i][j]);
        }
    }

    scanf("%s", str);
    scanf("%d", &P);

    int stat=0, p=0;
    for (int i=0; i<N; ++i) {
        if (str[i] == 'Y') {
            stat |= 1<<i;
            p++;
        }
    }

    if (p==0){
        if (P==0)printf("0\n");
        else printf("-1\n");
    }
    else if (p>=P){
        printf("0\n");
    }
    else {
        int answer = tsp(stat, p);
        printf("%d\n", answer);
    }

    return 0;
}
