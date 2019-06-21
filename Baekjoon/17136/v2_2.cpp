/**
 * Using Vector to reduce time.
 */
#include <cstdio>
#include <vector>
#include <math.h>
#include <utility>

using namespace std;

int N=10;
int arr[15][15];
int rec[6];//check using rec cnt.
int answer=-1;
vector<pair<int,int> > v;

bool check(int x, int y, int len) {
    if (rec[len]>=5)return false;
    int i,j;
    for (i=x; i<x+len; ++i) {
        for (j=y; j<y+len; ++j) {
            if (arr[i][j]==0)return false;
        }
    }
    return true;
}

void fill(int x, int y, int len, int data) {
    int i,j;
    for (i=x; i<x+len; ++i) {
        for (j=y; j<y+len; ++j) {
            arr[i][j]=data;
        }
    }    
}

bool solve(int len, int sum, int cnt) {
    if (sum < 0 || cnt > 24)return false;
    else if (sum == 0) {
        answer = cnt;
        return true;
    }

    for (; len>0; --len) {
        if (sum < len*len)continue;
        
        vector<pair<int,int> >::iterator itr;
        for (itr=v.begin(); itr!=v.end(); ++itr) {
            int x = (*itr).first;
            int y = (*itr).second;
            if (check(x,y,len)) {
                rec[len]++;
                fill(x,y,len,0);
                if (solve(len,sum-(len*len), cnt+1))return true;
                fill(x,y,len,1);
                rec[len]--;
            }
        }
    }
    
    return false;
}

int main(void) {
    int i,j,sum=0;
    int tmp[10][10];
    for (i=0; i<N; ++i) {
        for (j=0; j<N; ++j) {
            scanf("%d", &arr[i][j]);
            sum+=arr[i][j];
            if (arr[i][j]==1)v.push_back(make_pair(i,j));
        }
    }

    for (i=1; i<=5; ++i) {
        rec[i]=0;
    }

    int len;
    for (len=5; len>=0; --len) {
        if (sum < len*len)continue;

        solve(len,sum,0);
        if (answer != -1)break;
    }

    printf("%d\n", answer);

    return 0;
}
