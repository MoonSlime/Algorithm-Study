#include <iostream>
#include <vector>
#include <cstring>

#define MAX 1001

using namespace std;

int N=0,M=0;
bool visit[MAX];
vector<int> book(MAX);
vector<vector<int> > adj(MAX);

void init() {
    for (int i=0; i<=N; ++i) {
        adj[i].clear();
        adj[i].push_back(0);
        adj[i].push_back(0);
    }

    for (int i=0; i<=M; ++i) {
        book[i]=0;
    }
}

bool match(int person) {
    if (visit[person])return false;
    visit[person] = true;

    int a=adj[person][0];
    int b=adj[person][1];

    while(a<=b) {
        if (book[a]==0 || match(book[a])) {
            book[a]=person;
            return true;
        }
        a++;
    }

    return false;
}

int main(void) {
    int T;
    cin >> T;

    for (int t=0; t<T; ++t) {
        cin >> N >> M;

        init();

        for (int m=1; m<=M; ++m) {
            int a,b;
            cin >> a >> b;
            adj[m][0]=a;
            adj[m][1]=b;
        }

        int answer=0;
        for (int m=1; m<=M; ++m) {
            memset(visit, false, sizeof(bool)*m);
            if (match(m))answer++;
        }
        cout << answer << endl;
    }

    return 0;
}
