/**
 * 시간초과의 원인이 cin,cout을 사용한 입출력에 있을거라 생각하여,
 * printf, scanf를 사용하도록 수정하였지만 여전히 시간초과.
 */
#include <vector>
#include <stdio.h>

using namespace std;

int N,M,v_count=0;
int visit[1001]={0,}, work[1001]={0,};
vector<vector<int> > adj;

bool match(int emp) {
    if (visit[emp]==v_count)return false;
    visit[emp] = v_count;

    vector<int> cur = adj[emp];

    for (int i=0; i<cur.size(); ++i) {
        if (work[cur[i]]==0 || match(work[cur[i]])) {
            work[cur[i]]=cur[i];
            return true;
        }
    }

    return false;
}

int main(void) {
    scanf("%d %d", &N, &M);

    adj.resize(N+2);
    
    int a,b;
    for (int i=1; i<=N; ++i) {
        scanf("%d", &a);
        while (a--) {
            scanf("%d", &b);
            adj[i].push_back(b);
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
