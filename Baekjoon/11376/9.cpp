#include <iostream>
#include <vector>
#include <cstring>

#define MAX 1001

using namespace std;

int N,M;

vector<vector<int> > adj;
int visit[MAX], work[MAX];
int visitCnt=0;

bool match(int emp) {
    if (visit[emp]==visitCnt)return false;
    visit[emp]=visitCnt;

    vector<int> cur = adj[emp];
    for (int i=0; i<cur.size(); ++i) {
        if (work[cur[i]]==0 || match(work[cur[i]])) {
            work[cur[i]] = emp;
            return true;
        }
    }
    return false;
}

int main(void) {
    cin >> N >> M;
    adj.resize(N+2);

    register int a,b;
    for (register int i=1; i<=N; ++i) {
        cin >> a;
        while (a--) {
            cin >> b;
            adj[i].push_back(b);
        }
    }

    int answer=0;
    for (int i=1; i<=N; ++i) {
        for (int j=0; j<2; ++j) {
            visitCnt++;
            if (match(i))answer++;
        }
    }
    cout << answer;

    return 0;
}
