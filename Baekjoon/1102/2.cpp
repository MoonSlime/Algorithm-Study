#include <cstdio>
#include <cmath>
#include <algorithm>

#define INF 100000

using namespace std;

char str[17];
int N, P, cost[16][16], D[16][(int)(1<<16)];
//D[i][j] == i발전기를 마지막으로 켰을때, j 상태.

int tsp(int cur, int stat, int p) {
    if (p == P) {
        //return D[cur][stat];// == return 0;
        return 0;// == return 0;
    }

    D[cur][stat] = INF;
    for (int i=0; i<N; ++i) {
        if ((stat & (1<<i))==0)continue;
        for (int j=0; j<N; ++j) {
            if ((stat&(1<<j))==0 && cost[cur][i]>=0) {
                D[i][stat] = min(D[i][stat], tsp(i, stat|
            }
        }
    }
    for (int i=0; i<N; ++i) {
        //cost >0 or cost >=0 ???
        if ((stat & (1<<i)) == 0 && str[i]=='N' && cost[cur][i]>=0) {
            //D[i][stat | (1<<i)] = min(INF, tsp(i, stat|(1<<i), p+1) + );
            D[cur][stat] = min(D[cur][stat], tsp(i, stat|(1<<i), p+1) + cost[cur][i]);
        }
    }

    return D[cur][stat];
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

    int stat=0;
    for (int i=0; i<N; ++i) {
        if (str[i] == 'Y') {
            stat |= 1<<i;
            P--;
        }
    }

    int answer=INF;
    for (int i=0; i<N; ++i) {
        if (str[i]=='Y')answer = min(answer, tsp(i, stat, 0));
    }

    printf("%d\n", answer);

    return 0;
}
