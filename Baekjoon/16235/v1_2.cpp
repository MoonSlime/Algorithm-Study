#include <iostream>
#include <algorithm>
#include <utility>
#include <math.h>
#include <vector>
#include <map>

#define incode(r,c) (r*12)+c 
#define r(data) data/12
#define c(data) data%12

using namespace std;

int N,M,K,A[12][12],MAP[12][12];//1<=N<=10, 1<=M<=100
map<int, vector<int> > tree;//tree[incode(data)].push_back(age);

bool compare(int x, int y) {
    return x<y;
}

void next_year() {
    map<int, vector<int> >::iterator itr;
    //봄
    for (itr=tree.begin(); itr!=tree.end(); ++itr) {
        int r = r(itr->first);
        int c = c(itr->first);

        if (r<1 || r>10 || c<1 || c>10)continue;

        vector<int>::iterator v_itr = itr->second.begin();
        for (;v_itr!=itr->second.end();++v_itr) {
            if (MAP[r][c] >= *v_itr) {
                MAP[r][c]-=*v_itr;
                *v_itr += 1;
            }
            else {
                //여름(Sorting 되어있기때문에 가능.)
                while (v_itr!=itr->second.end()) {
                    MAP[r][c] += (*v_itr)/2;
                    itr->second.erase(v_itr);
                }
                break;
            }
        }
    }
/**
    //정렬필요없을듯.
    for (itr=tree.begin(); itr!=tree.end(); ++itr) {
    sort(itr->second.begin(), itr->second.end(), compare);
    }
**/
    //가을
    map<int, vector<int> >::iterator end = tree.end();
    for (itr=tree.begin(); itr!=end; ++itr) {
        int data = itr->first;
        int r = r(data);
        int c = c(data);
        if (r<1 || r>10 || c<1 || c>10)continue;

        vector<int>::iterator v_itr = itr->second.begin();
        for (;v_itr!=itr->second.end(); ++v_itr) {
            if ((*v_itr)%5!=0)continue;

            tree[data-13].insert(tree[data-13].begin(), 1);
            tree[data-12].insert(tree[data-12].begin(), 1);
            tree[data-11].insert(tree[data-11].begin(), 1);
            tree[data-1].insert(tree[data-1].begin(), 1);
            tree[data+1].insert(tree[data+1].begin(), 1);
            tree[data+11].insert(tree[data+11].begin(), 1);
            tree[data+12].insert(tree[data+12].begin(), 1);
            tree[data+13].insert(tree[data+13].begin(), 1);
        }
    }  

    //겨울
    for (int i=1; i<=N; ++i) {
        for (int j=1; j<=N; ++j) {
            MAP[i][j] += A[i][j];
        }
    }
}

int main(void) {
    cin >> N >> M >> K;

    for (int i=1; i<=N; ++i) {
        for (int j=1; j<=N; ++j) {
            cin >> A[i][j];
            MAP[i][j] = 5;
        }
    }

    /**
    //Tree Vector Initialize
    for (int i=1; i<=10; ++i) {
    for (int j=1; j<=10; ++j) {
    vector<int> new_v;
    tree.push_back(new_v);
    }
    }
     **/

    for (int i=1; i<=M; ++i) {
        int r,c,age;
        cin >> r >> c >> age;
        tree[incode(r,c)].push_back(age);
    }

    map<int, vector<int> >::iterator itr;
    for (itr=tree.begin(); itr!=tree.end(); ++itr) {
        sort(itr->second.begin(), itr->second.end(), compare);
    }

    for (int i=0; i<K; ++i) {
//        cout << "NEXT YEAR"<<endl;
        next_year();
    }

    long long answer=0;
    for (itr=tree.begin(); itr!=tree.end(); ++itr) {
        int data = itr->first;
        int r = r(data);
        int c = c(data);
        if (r<1 || r>10 || c<1 || c>10)continue;
  //      cout << r(data) <<',' << c(data) << "=> "<<itr->second.size()<<endl;
        answer += itr->second.size(); 
    }

    cout << answer << endl;

    return 0;
}
