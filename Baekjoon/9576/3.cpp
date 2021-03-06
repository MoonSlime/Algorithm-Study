#include <iostream>
#include <vector>
#include <cstring>

#define MAX 1001

using namespace std;

int N=0,M=0,visitCnt=0;
int visit[MAX], book[MAX];
int adj[MAX][2];

bool match(int person) {
    if (visit[person]==visitCnt)return false;
    visit[person] = visitCnt;

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

        for (int m=1; m<=M; ++m) {
            int a,b;
            cin >> a >> b;
            adj[m][0]=a;
            adj[m][1]=b;
        }

        for (int n=1; n<=N; ++n) {
            book[n]=0;
        }

        int answer=0;
        for (int m=1; m<=M; ++m) {
            visitCnt++;
            if (match(m))answer++;
        }

        if (t>0)cout << endl;
        cout << answer;
    }

    return 0;
}
