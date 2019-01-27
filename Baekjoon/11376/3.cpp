#include <iostream>
#include <vector>

using namespace std;

int N,M,Max=0;

vector<int> emp(1001,0);
vector< vector<int> > work(1001,vector<int>(0,0));

void print1(vector<int> v) {
    for (int i=1; i<N; ++i) {
        cout << v[i]<<endl;
    }
    cout << endl;
}

void print2(vector< vector<int> > v) {
    for (int i=0; i<N; ++i) {
        for (int j=0; j<2; ++j) {
            cout << v[i][j] << ' ';
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
    if (cnt + M - idx < Max)return true;

    bool ret=false;

    for (int i=0; i<work[idx].size(); ++i) {
        if (emp[work[idx][i]]==0)continue;
        emp[work[idx][i]]--;
        ret = solve(idx+1, cnt+1);
        emp[work[idx][i]]++;
        if (ret)return ret;
    }
    ret = solve(idx+1, cnt);

    return ret;
}

int main(void) {
    cin >> N >> M;
    
    int tmp;
    
    for (int i=1; i<=N; ++i) {
        cin >> emp[i];
        for (int j=0; j<emp[i]; ++j) {
            cin >> tmp;
            work[tmp].push_back(i);
        }
    }

    print1(emp);
    print2(work);

    solve(0, 0);

    cout << Max << endl;

    return 0;
}
