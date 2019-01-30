/**
 * version 3
 * 시간초과 해결을위하여 vector -> int를사용한 배열로 변경.
 * 시간초과 해결.
 * (메모리를 좀더 사용하여 시간을 줄일 수 있는 방법이 있는지 확인.)
 */
#include <vector>
#include <stdio.h>

using namespace std;

int N,M,v_count=0;
int visit[1001], work[1001];
int adj[1001][1001];

bool match(int emp) {
    if (visit[emp]==v_count)return false;
    visit[emp] = v_count;

    for (int i=0; adj[emp][i]!=0; ++i) {
        int x = adj[emp][i];
        if (work[x]==0 || match(work[x])) {
            work[x]=emp;
            return true;
        }
    }

    return false;
}

int main(void) {
    scanf("%d %d", &N, &M);
    
    int a;
    for (int i=1; i<=N; ++i) {
        scanf("%d", &a);
        while (a--) {
            scanf("%d", &adj[i][a]);
        }
    }

    int answer=0;
    for (int i=1; i<=N; ++i) {
        v_count++;
        if (match(i))answer++;
    }

    printf("%d\n", answer);

    return 0;
}
