/**
 * Change pair<int, int> to struct PAIR
 */

#include <iostream>
#include <vector>
#include <string>
#include <queue>

#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

using namespace std;

typedef struct _PAIR {
    int rx,ry,bx,by;
    _PAIR(){}
    _PAIR(int a,int b,int c,int d):rx(a),ry(b),bx(c),by(d){}
}PAIR;

int bias[4][2] = {{-1,0}, {1,0}, {0,-1}, {0,1}};

int N,M;
vector<string> v;

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    scanf("%d %d", &N, &M);

    PAIR p;

    for (int i=0; i<N; ++i) {
        string tmp;
        cin >> tmp;
        v.push_back(tmp);

        for (int j=1; j<=M; ++j) {
            if (tmp[j]=='R') {
                p.rx = i;
                p.ry = j;
            }
            else if (tmp[j]=='B') {
                p.bx = i;
                p.by = j;
            }
        }
    }

    queue<PAIR> q, tmp_q;
    q.push(p);

    int answer=0;

    while (answer < 10) {
        answer++;

        bool check=false;
        while(!q.empty()) {
            PAIR p = q.front();
            int rx,ry,bx,by;
            char next;
            bool change;
/**
            cout << p.rx <<", ";
            cout << p.ry <<", ";
            cout << p.bx <<", ";
            cout << p.by <<", "<<endl;
**/
            for (int mode=0; mode<4; ++mode) {
                if (mode==UP && ry==by && rx>bx) {
                    rx=p.bx;ry=p.by;
                    bx=p.rx;by=p.ry;
                    change=true;
                }
                else if (mode==DOWN && ry==by && rx<bx) {
                    rx=p.bx;ry=p.by;
                    bx=p.rx;by=p.ry;
                    change=true;
                }
                else if (mode==LEFT && rx==bx && ry>by) {
                    rx=p.bx;ry=p.by;
                    bx=p.rx;by=p.ry;
                    change=true;
                }
                else if (mode==RIGHT && rx==bx && ry<by) {
                    rx=p.bx;ry=p.by;
                    bx=p.rx;by=p.ry;
                    change=true;
                }
                else {
                    rx=p.rx;ry=p.ry;
                    bx=p.bx;by=p.by;
                    change=false;
                }

                //move R
                while (true) {
                    next = v[rx+bias[mode][0]][ry+bias[mode][1]];
                    if (next == '#')break;
                    else if (next == 'O') {
                        rx=0;
                        ry=0;
                        break;
                    }
                    else ;
                    rx += bias[mode][0];
                    ry += bias[mode][1];
                }

                //move B
                while (true) {
                    next = v[bx+bias[mode][0]][by+bias[mode][1]];
                    if (next == '#' || (bx-1==rx && by==ry))break;
                    else if (next == 'O') {
                        bx=0;
                        by=0;
                        break;
                    }
                    else ;
                    bx += bias[mode][0];
                    by += bias[mode][1];
                }

                if (!change) {
                    if (rx==0 && ry==0 && bx!=0 && by!=0) {
                        check=true;
                        break;
                    }
                    else if (rx!=0 && ry!=0 && bx!=0 && by!=0) {
                        p.rx = rx;
                        p.ry = ry;
                        p.bx = bx;
                        p.by = by;
                        tmp_q.push(p);
                    }
                }
                else {
                    if (bx==0 && by==0 && rx!=0 && ry!=0) {
                        check=true;
                        break;
                    }
                    else if (rx!=0 && ry!=0 && bx!=0 && by!=0) {
                        p.rx = bx;
                        p.ry = by;
                        p.bx = rx;
                        p.by = ry;
                        tmp_q.push(p);
                    }
                }
            }
            q.pop();
        }
        //if (!q.empty())break;
        if (check)break;

        q = tmp_q;
    }

    if (answer==10)cout << -1 <<endl;
    else cout << answer<< endl;

    return 0;
}
