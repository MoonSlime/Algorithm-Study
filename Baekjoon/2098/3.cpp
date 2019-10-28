#include <cstdio>
#include <cmath>
#include <algorithm>

#define DEBUG 0
//#define END (int)(pow(2,16)-1)
#define MAX 16

using namespace std;

int END;
int N, arr[16][16], D[16][1<<16];//D[i][j]==i도시에 도착했을때, j인덱스 만큼인 값.

void tsp(int cur, int idx) {
    if (idx == END-1) {
        
        if (arr[cur][0] == 0)return ;
        else if (D[0][END] == 0)D[0][END] = D[cur][idx] + arr[cur][0];
        else D[0][END] = min(D[0][END], D[cur][idx] + arr[cur][0]);
        
        return ;
    }
    
    for (int i=1; i<N; ++i) {
        if ((idx & (1<<i)) > 0 || arr[cur][i]==0)continue;

        int tmp = D[cur][idx] + arr[cur][i];
        if (D[i][idx|(1<<i)]!=0 && D[i][idx|(1<<i)] < tmp)continue;
        else D[i][idx|(1<<i)] = tmp;

        tsp(i, idx|(1<<i));
    }
}

int main(void) {
    scanf("%d", &N);

    END = (int)(1<<N) - 1;

    for (int i=0; i<N; ++i) {
        for (int j=0; j<N; ++j) {
            scanf("%d", &arr[i][j]);
        }
    }

    //Start&End ==  0.
    for (int i=1; i<N; ++i) {
        if (arr[0][i]==0)continue;
        D[i][1<<i] = arr[0][i];
        tsp(i, 1<<i);//, D[i][1<<i]=arr[0][i]);
    }

    printf("%d\n", D[0][END]);
}
