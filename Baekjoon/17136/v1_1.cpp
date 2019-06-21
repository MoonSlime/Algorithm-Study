#include <cstdio>
#include <vector>
#include <math.h>

using namespace std;

int N=10;
int arr[20][20];
int rec[6];//check using rec cnt.
int answer=26, sum;

bool check(int x, int y, int len) {
    if (rec[len]>=5 || sum < len*len)return false;
    int i,j;
    for (i=x; i<x+len; ++i) {
        for (j=y; j<y+len; ++j) {
            if (arr[i][j] != 1)return false;
        }
    }
    return true;
}

//1->0
void erase(int x, int y, int len) {
    int i,j;
    for (i=x; i<x+len; ++i) {
        for (j=y; j<y+len; ++j) {
            arr[i][j]=0;
        }
    }    
    rec[len]++;
    sum-=len*len;
}

//0->1
void fill(int x, int y, int len) {
    int i,j;
    for (i=x; i<x+len; ++i) {
        for (j=y; j<y+len; ++j) {
            arr[i][j]=1;
        }
    }    
    rec[len]--;
    sum+=len*len;
}

void solve(int len, int cnt) {
    if (sum < 0 || cnt >= answer)return ;
    else if (sum == 0) {
        answer = min(answer, cnt);
    }

    int i,j,k;
    for (i=5; i<N+5; ++i) {
        if (sum < len*len)break;
        for (j=5; j<N+5; ++j) {
            if (sum < len*len)break;
            for (k=len; k>0; --k) {
                if (sum < k*k)break;
                if (check(i,j,k)) {
                    erase(i,j,k);
                    solve(k, cnt+1);
                    fill(i,j,k);
                }
            }
        }
    }
}

int main(void) {
    int i,j;
    int tmp[20][20];
    for (i=5; i<N+5; ++i) {
        for (j=5; j<N+5; ++j) {
            scanf("%d", &tmp[i][j]);
            sum+=tmp[i][j];
        }
    }

    for (i=1; i<=5; ++i) {
        rec[i]=0;
    }

    int len;
    for (len=0; len<=5; ++len) {
        if (sum > len*len*5)continue;
    
        for (i=5; i<N+5; ++i) {
            for (j=5; j<N+5; ++j) {
                arr[i][j] = tmp[i][j];
            }
        }

        solve(len,0);
    }

    if (answer==26)answer=-1;
    printf("%d\n", answer);

    return 0;
}
