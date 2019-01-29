#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

int N,M;

vector<vector<int> > adj;
int visit[201], home[201];
int visitCnt=0;

bool match(int cow) {
    if (visit[cow]==visitCnt)return false;
    visit[cow]=visitCnt;

    vector<int> cur = adj[cow];
    for (int i=0; i<cur.size(); ++i) {
        if (home[cur[i]]==0 || match(home[cur[i]])) {
            home[cur[i]] = cow;
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
        visitCnt++;
        if (match(i))answer++;
    }
    cout << answer;

    return 0;
}
