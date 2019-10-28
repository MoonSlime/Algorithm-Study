#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <utility>


using namespace std;

#define PAIR pair<int, int>

int N,M;
vector<string> v;

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    scanf("%d %d", &N, &M);

    PAIR R,B;

    for (int i=0; i<N; ++i) {
        string tmp;
        cin >> tmp;
        v.push_back(tmp);

        for (int j=1; j<=M; ++j) {
            if (tmp[j]=='R') {
                R = make_pair(i,j);
            }
            else if (tmp[j]=='B') {
                B = make_pair(i,j);
            }
        }
    }

    queue< PAIR < PAIR, PAIR >  > q, q_tmp;
    q.push(make_pair(R,B));

    int answer=0;

    while (answer < 10) {
        answer++;

        while(!q.empty()) {
            PPAIR pp = q.front();
            PAIR R = pp.first, B = pp.second;
            int rx,ry,bx,by;
            char next;
            bool change;
            
            if (ry==by && rx>bx) {
                rx=B.first;ry=B.second;
                bx=R.first;by=R.second;
                change=true;
            }
            else {
                rx=R.first;ry=R.second;
                bx=B.first;by=B.second;
                change=false;
            }

            //move R
            while (true) {
                next = v[rx-1][ry];
                if (next == '#')break;
                else if (next == 'O') {
                    rx=0;
                    ry=0;
                    break;
                }
                else continue;
            }

            //move B
            while (true) {
                next = v[bx-1][by];
                if (next == '#' || (bx-1==rx && by==ry))break;
                else if (next == 'O') {
                    bx=0;
                    by=0;
                    break;
                }
                else continue;
            }
           
            if (!change) {
                if (rx==0 && ry==0 && bx!=0 && by!=0)break;
                else if (rx!=0 && ry!=0 && bx!=0 && by!=0) {
                    tmp_q.push(make_pair(make_pair(rx,ry),make_pair(bx,by)));
                }
            }
            else {
                if (bx==0 && by==0 && rx!=0 && ry!=0)break;
                else if (rx!=0 && ry!=0 && bx!=0 && by!=0) {
                    tmp_q.push(make_pair(make_pair(bx,by),make_pair(rx,ry)));
            }

            q.pop();
        }

        if (!q.empty())break;
        q = tmp_q;
    }

    if (answer==10)cout << -1 <<endl;
    else cout << answer<< endl;

    return 0;
}
