#include <iostream>
#include <utility>
#include <math.h>
#include <vector>

#define incode(r,c) (r*12)+c 
#define r(x) data/12
#define c(x) data%12

using namespace std;

int N,M,K,A[12][12];//1<=N<=10, 1<=M<=100
vector<vector<int> > tree;//tree[incode(data)].push_back(age);

int main(void) {
    cin >> N >> M >> K;

    for (int i=1; i<=N; ++i) {
        for (int j=1; j<=N; ++j) {
            cin >> A[i][j];
            A[i][j]+=5;
        }
    }

    //Tree Vector Initialize
    for (int i=1; i<=10; ++i) {
        for (int j=1; j<=10; ++j) {
            vector<int> new_v;
            tree.push_back(new_v);
        }
    }

    for (int i=1; i<=M; ++i) {
        int r,c,age;
        cin >> r >> c >> age;
        tree[incode(r,c)].push_back(age);
    }

    for (int i=1; i<=10; ++i) {
        for (int j=1; j<=10; ++j) {
            vector<int> cur = tree[incode(i,j)];
            for (int k=0; k<cur.size(); ++k) {
                cout << i << ',' << j << "=>" << cur[k]<<endl;
            }
        }
    }

    return 0;
}
