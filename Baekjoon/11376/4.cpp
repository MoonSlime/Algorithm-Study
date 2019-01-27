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

    /**
    for (int i=0; i<=M; ++i) {
        vector<int> elem;
        work.push_back(elem);
    }**/
        

    for (int i=1; i<=N; ++i) {
        cin >> emp[i];
        for (int j=0; j<emp[i]; ++j) {
            int tmp;
            cin >> tmp;
//            cout << "work["<<tmp<<"]"<<".push("<<i<<")"<<endl;
            work[tmp].push_back(i);
//            cout << work[tmp].back()<<endl;
        }
    }

//    print();

    solve(1, 0);

    cout << Max << endl;

    return 0;
}
