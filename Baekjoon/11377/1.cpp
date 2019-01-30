/**
 *
 * version 1 은 아래의 예시와 같은 경우 만족하지 않음.
 * (k를 먼저 소진해버린 경우, k를 다시 회수할 수 없음.)
 5 5 1
 3 1 2 3
 3 1 4 5
 1 1
 1 2
 1 1
 *
 * version 2 는 k를 우선 소비하지 않고, 직원 각각에게 일을 하나씩 배정한 후,
 * k를 하나씩 추가 배정한다. (제출 성공.)
 *
 */
#include <stdio.h>

int N,M,K,vc=0;//vc == visit_Count
int adj[1001][1001], visit[1001], work[1001];

int k=0;

bool match(int emp) {
    if (visit[emp]==vc+1)return false;
    if (visit[emp]==vc) {
        if (!(k<K))return false;
        visit[emp]++;
        k++;
    }
    else {
        visit[emp]=vc;
    }

    int x=adj[emp][0];
    for (int i=0; x!=0; x=adj[emp][++i]) {
        if (work[x]==0 || match(work[x])) {
            work[x]=emp;
  //          printf("work[%d]=%d\n",x,emp);
            return true;
        }
    }

    if (visit[emp]==vc+1)k--;

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
        vc+=2;
        for (int j=0; j<2; ++j) {
        if (match(i))answer++;
//        printf("\n");
        }
    }

    printf("%d", answer);

    return 0;
}
