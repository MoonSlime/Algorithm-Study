#include <cstdio>
#include <vector>
#include <math.h>
#include <utility>

using namespace std;

int N=10;
int arr[15][15], visit[15][15];
int rec[6];//check using rec cnt.
int answer=26;
vector<pair<int,int> > v;

bool check(int x, int y, int len) {
    int i,j;
    for (i=x; i<x+len; ++i) {
        for (j=y; j<y+len; ++j) {
            if (arr[i][j]==0 || visit[i][j]==1)return false;
        }
    }
    printf("CHECK %d,%d [len = %d] => true\n",x,y, len);
    return true;
}

void visit_fill(int x, int y, int len, int data) {
    printf("[%d] %d,%d, len = %d\n", data, x, y, len);
    int i,j;
    for (i=x; i<x+len; ++i) {
        for (j=y; j<y+len; ++j) {
            visit[i][j] = data;
        }
    }    
}

bool solve(int sum, int cnt) {
    if (sum < 0 || cnt >= answer)return false;
    else if (sum == 0) {
        answer = min(answer, cnt);
        return true;
    }

    printf("NEW SOLVE\n");

    int len;
    for (len=5; len>0; --len) {
        if (sum < len*len || rec[len] == 0)continue;
    
        vector<pair<int, int> >::iterator itr;
        for (itr=v.begin(); itr!=v.end(); ++itr) {
            int x = (*itr).first;
            int y = (*itr).second;
            if (check(x,y,len)) {
                rec[len]--;
                visit_fill(x,y,len, 1);
                //if (solve(sum-(len*len), cnt+1))return true;
                solve(sum-(len*len), cnt+1);
                printf("SOLVE END\n");
                visit_fill(x,y,len, 0);
                rec[len]++;
            }
        }
    }


    return false;
}

int main(void) {
    int i,j,sum=0;
    for (i=0; i<N; ++i) {
        for (j=0; j<N; ++j) {
            scanf("%d", &arr[i][j]);
            sum+=arr[i][j];
            if (arr[i][j]==1)v.push_back(make_pair(i,j));
        }
    }

    for (i=1; i<6; ++i) {
        rec[i]=5;
    }

    solve(sum, 0);
    if (answer == 26)answer = -1;
    printf("%d\n", answer);
    return 0;
}
