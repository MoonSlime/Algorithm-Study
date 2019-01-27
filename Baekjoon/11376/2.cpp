#include <iostream>
#include <vector>

using namespace std;

int N,M,Max=0;

vector< vector<int> > emp;//
vector<int> work(1001, 0);

void print() {
    for (int i=0; i<emp.size(); ++i) {
        for (int j=0; j<emp[i].size(); ++j) {
            cout << emp[i][j];
        }
        cout << endl;
    }
}

bool solve(int idx, int cnt) {
    if (idx == emp.size()) {
        Max = max(Max, cnt);
        return false;
    }
    if (cnt + (N-idx)*2 < Max)return true;

    bool ret=false;

    for (int i=0; i<emp[idx].size(); ++i) {
        if (work[emp[idx][i]]!=0)continue;
        work[emp[idx][i]] = 1;
        for (int j=i+1; j<emp[idx].size(); ++j) {
            if (work[emp[idx][j]]!=0)continue;
            work[emp[idx][j]] = 1;
            ret = solve(idx+1, cnt+2);
            work[emp[idx][j]] = 0;
            if (ret) {
                work[emp[idx][i]]=0;
                return true;
            }
        }
        ret = solve(idx+1, cnt+1);
        work[emp[idx][i]] =0;
        if (ret)return true;
    }

    if (solve(idx+1, cnt))return true;
    
    return false;
}

int main(void) {
    cin >> N >> M;
    
    int a,b;
    for (int i=0; i<N; ++i) {
        cin >> a;
        vector<int> element;
        for (int j=0; j<a; ++j) {
            cin >> b;
            element.push_back(b);
        }
        emp.push_back(element);
    }

    solve(0, 0);

    cout << Max<<endl;

    //print();

    return 0;
}
