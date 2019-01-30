/**
 * 현재 시간 초과 발생. 
 * cin을 사용한 입력방식이 문제인것으로 파악.
 * version 2 에서는 cin -> scanf 를 사용하여 풀어봄.
 *
 * version 2도 실패하여 sync_with_stdio를 false해보았으나 마찬가지.
 *
 * version 3에서는 vector -> int배열로 바꾸어 보려 한다. (시간초과 해결!!)
 *
 * 검색하다보니 hopkroft karp algorithm 을 공부해서 해보는 것도 좋을 것 같다.
 *
 */
#include <iostream>
#include <vector>

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
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> N >> M;

    adj.resize(N+2);
    
    int a,b;
    for (int i=1; i<=N; ++i) {
        cin >> a;
        while (a--) {
            cin >> b;
            adj[i].push_back(b);
        }
    }

    int answer=0;
    for (int i=1; i<=N; ++i) {
        v_count++;
        if (match(i))answer++;
    }

    cout << answer;

    return 0;
}
