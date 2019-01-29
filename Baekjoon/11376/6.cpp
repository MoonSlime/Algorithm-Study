#include <iostream>
#include <vector>

using namespace std;

int N,M,Max=0;

int emp[1001];
vector< vector<int> > work(1001, vector<int>(0,0));
vector<int> q;

void print() {
    for (int i=1; i<=M; ++i) {
        for (int j=0; j<work[i].size(); j++) {
            cout << work[i][j]<<' ';
        }
        cout << endl;
    }
    cout << endl;
}

bool solve(int idx, int cnt) {
    if (idx == M+1) {
        Max = max(Max, cnt);
        return true;
    }
    if (cnt + M+1 - idx < Max)return false;

    for (int i=0; i<work[idx].size(); ++i) {
        if (emp[work[idx][i]]==2)continue;
        emp[work[idx][i]]++;
        //q.push_back(work[idx][i]);
        solve(idx+1, cnt+1);
        //q.pop_back();
        emp[work[idx][i]]--;
    }
    solve(idx+1, cnt);

    return true;
}

int main(void) {
    cin >> N >> M;

    int a,b;
    for (int i=1; i<=N; ++i) {
        cin >> a;
        for (int j=0; j<a; ++j) {
            cin >> b;
            work[b].push_back(i);
        }
    }

    solve(1, 0);

    cout << Max << endl;

//    print();

    return 0;
}
