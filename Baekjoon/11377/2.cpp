/**
 * version 2.
 *
 * 제출에는 성공하였으나 빠른 해결방법과 시간차이가 약 두배이상 남
 * (현재 코드도 느린편은 아님.)
 *
 * 다른 방법이 있을지 생각해보자.
 *
 */

#include <stdio.h>

int N,M,K,vc=0;//vc == visit_Count
int adj[1001][1001], visit[1001], work[1001];

bool match(int emp) {
    if (visit[emp]==vc)return false;
    visit[emp]=vc;

    int x=adj[emp][0];
    for (int i=0; x!=0; x=adj[emp][++i]) {
        if (work[x]==0 || match(work[x])) {
            work[x]=emp;
            return true;
        }
    }

    return false;
}

int main(void) {
    scanf("%d %d %d",&N,&M,&K);

    int a;
    for (int i=1; i<=N; ++i) {
        scanf("%d",&a);
        while(a--) {
            scanf("%d", &adj[i][a]);
        }
    }

    int answer=0;
    for (int i=1; i<=N; ++i) {
        vc++;
        if (match(i))answer++;
    }

    int k=0;
    for (int i=1; i<=N && k<K; ++i) {
        vc++;
        if (match(i)) {
            answer++;
            k++;
        }
    }

    printf("%d", answer);

    return 0;
}
