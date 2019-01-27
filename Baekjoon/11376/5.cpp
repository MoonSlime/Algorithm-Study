#include <iostream>
#include <vector>

using namespace std;

int N,M,Max=0;

int emp[1001];
vector< vector<int> > work(1001, vector<int>(0,0));

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
        return false;
    }
    if (cnt + M - idx + 1< Max)return true;

    bool ret=false;

    for (int i=0; i<work[idx].size(); ++i) {
        if (emp[work[idx][i]]==2)continue;
        emp[work[idx][i]]++;
//        cout << work[idx][i]<<" work=> "<< idx<<endl;
        ret = solve(idx+1, cnt+1);
//        cout << work[idx][i]<<" minus=> "<< idx<<endl;
        emp[work[idx][i]]--;
        if (ret)return ret;
    }
    ret = solve(idx+1, cnt);

    return ret;
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
