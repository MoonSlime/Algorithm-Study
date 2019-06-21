#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>

using namespace std;

int N,C;
vector<int> obj;

bool cmp(int x,int y) {
    return x<y;
}

int solve(int idx, int weight) {
    if (idx == obj.size() || weight==0)return 1;

    int ret = 0;

    if (weight-obj[idx]>=0){
        ret += solve(idx+1, weight);
        ret += solve(idx+1, weight-obj[idx]);
    }
    else ret+=solve(idx+1, weight);

    return ret;
}

int main(void) {
    cin >> N >> C;

    for (int i=0; i<N; ++i) {
        int w;
        cin >> w;
        obj.push_back(w);
    }

    sort(obj.begin(), obj.end(), cmp);

    cout << solve(0, C) << endl;

    return 0;
}
