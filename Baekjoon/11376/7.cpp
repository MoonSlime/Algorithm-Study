#include <iostream>
#include <vector>

using namespace std;

int N,M,Max=0;

vector<bool> work(1001, false);
vector< vector<int> > emp;

bool solve(int idx, int cnt) {
    if (idx == emp.size()) {
        Max = max(Max, cnt);
        return true;
    }
    if (cnt + (emp.size() - idx)*2 < Max)return false;

    vector<int> cur = emp[idx];

    for (int i=0; i<cur.size(); ++i) {
        if (work[cur[i]])continue;
        work[cur[i]]=true;
        for (int j=i+1; j<cur.size(); ++j) {
            if (work[cur[j]])continue;
            work[cur[j]]=true;
            solve(idx+1, cnt+2);
            work[cur[j]]=false;
        }
        solve(idx+1, cnt+1);
        work[cur[i]]=false;
    }
    solve(idx+1, cnt);

    return true;
}

int main(void) {
    cin >> N >> M;

    int cnt=0;
    int a,b;
    for (int i=1; i<=N; ++i) {
        cin >> a;
        vector<int> elem;
        for (int j=0; j<a; ++j) {
            cin >> b;
            if (a<=2 && !work[b]) {
                work[b]=true; 
                cnt++;
            }
            else elem.push_back(b);
        }
        if (a>2)emp.push_back(elem);
    }

    solve(0, cnt);

    cout << Max << endl;

    return 0;
}
