#include <iostream>
#include <vector>
#include <cstring>

#define MAX 1001

using namespace std;

int N,M;

vector<vector<int> > adj;
int work[MAX];
bool visit[MAX];

bool match(int emp) {
    if (visit[emp])return false;
    visit[emp]=true;

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
            memset(visit, false, sizeof(bool)*i);
            if (match(i))answer++;
        }
    }
    cout << answer;

    return 0;
}
