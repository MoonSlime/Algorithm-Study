#include <iostream>
#include <vector>
#include <cstring>
#include <cstdio>

using namespace std;

int N,M,Max=0;

bool visit[1001];
vector<int> work(1001, 0);
vector< vector<int> > emp;

bool match(int idx) {
    if (visit[idx])return false;
    visit[idx] = true;
    vector<int> cur = emp[idx];

    for (int i=0; i< cur.size(); ++i) {
        if (work[cur[i]]==0 || match(work[cur[i]])) {
            work[cur[i]]=idx;
            return true;
        }
    }

    return false;
}

int main(void) {
    cin >> N >> M;

    emp.resize(N+2);

    int cnt=0;
    int a,b;
    for (int i=1; i<=N; ++i) {
        cin >> a;
        for (int j=0; j<a; ++j) {
            cin >> b;
            emp[i].push_back(b);
        }
    }
   
    int answer=0;
    for (int i=1; i<=N; ++i) {
        for (int j=0; j<2; ++j) {
            memset(visit, false, sizeof(false)*1001);
            if (match(i))answer++;
        }
    }

    cout << answer;

    return 0;
}
