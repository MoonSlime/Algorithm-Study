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
//    printf("CHECK %d,%d [len = %d] => true\n",x,y, len);
    return true;
}

void visit_fill(int x, int y, int len, int data) {
    //printf("[%d] %d,%d, len = %d\n", data, x, y, len);
    int i,j;
    for (i=x; i<x+len; ++i) {
        for (j=y; j<y+len; ++j) {
            visit[i][j] = data;
        }
    }    
}

bool solve(int idx, int sum, int cnt) {
    if (sum < 0 || cnt >= answer || idx > v.size())return false;
    else if (sum == 0) {
        answer = min(answer, cnt);
        return true;
    }

    int x = v[idx].first;
    int y = v[idx].second;
    if (visit[x][y]==1) {
        solve(idx+1, sum, cnt);
        return false;
    }

    int len;
    for (len=5; len>0; --len) {
        if (sum < len*len || rec[len] == 0)continue;
    
        if (check(x,y,len)) {
            rec[len]--;
            visit_fill(x,y,len,1);
            solve(idx+1, sum-(len*len), cnt+1);
            visit_fill(x,y,len,0);
            rec[len]++;
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

    rec[0]=101;
    for (i=1; i<6; ++i) {
        rec[i]=5;
    }

    solve(0, sum, 0);
    if (answer == 26)answer = -1;
    printf("%d\n", answer);
    return 0;
}
