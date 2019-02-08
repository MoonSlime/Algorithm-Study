/**
 *
 * 1.cpp & 2.cpp 는 최대 이분매칭의 응용형식으로 풀어보려 하였으나 실패.
 *
 * -> 3.cpp까지하고 더 생각해보니 room[idx]==1이라고 그만할것이 아니라
 *  스위치를 두개다 켜는 경우는 생각하지 않아도 되나??
 */


#include <stdio.h>
#include <iostream>
#include <vector>

#define MAX 100001

using namespace std;

int N,M;
int room[MAX], visit[MAX], vc=1, btn_used[MAX];
vector<int> btn[MAX], rooms_btn[MAX];//rooms_btn[x].size() is always 2

int match(int idx) {
    if (room[idx]==1)return 1;
    printf("match(%d)\n", idx);
    printf("start\n");
    if (visit[idx]==vc)return 0;
    visit[idx]=vc;

    vector<int> cur = rooms_btn[idx];
    for (int i=0; i<cur.size(); ++i) {
  //      printf("====%d====\n",cur[i]);
        if (btn_used[cur[i]]==0) {
            btn_used[cur[i]]=1;

            int cur_btn=cur[i];
            printf("BTN[%d] using\n", cur_btn);
            for (int i=0; i<btn[cur_btn].size(); ++i) {
                room[btn[cur_btn][i]]+=1;
                room[btn[cur_btn][i]]%=2;
            }

            int ret=0;
            for (int i=0; i<btn[cur_btn].size(); ++i) {
                printf("call room[%d]\n", btn[cur_btn][i]);
                //if (btn[cur_btn][i]==idx)continue;
                if((ret = match(btn[cur_btn][i]))==0)break;
            }

            if (ret==0) {
                for (int i=0; i<btn[cur_btn].size(); ++i) {
                    room[btn[cur_btn][i]]+=1;
                    room[btn[cur_btn][i]]%=2;
                }
                btn_used[cur[i]]=0;
                return 0;
            }
            return 1;
        }
    }

    return 0;
}

int main() {
    //Input : N,M
    scanf("%d %d", &N, &M);

    //Input : room state
    for (int i=1; i<=N; ++i) {
        scanf("%d", &room[i]);
    }

    //Input : switch(btn) connected room.
    for (int i=1; i<=M; ++i) {
        int a;
        scanf("%d", &a);
    
        int b;
        for (int j=1; j<=a; ++j) {
            scanf("%d", &b);
            btn[i].push_back(b);
            rooms_btn[b].push_back(i);
//            printf("INPUT rooms_btn[%d].push(%d)\n", b, i);
        }
    }

    for (int i=1; i<=N; ++i) {
        vc++;
        printf("Master Call(%d)\n", i);
        if (match(i)==0){
            printf("0\n");
            return 0;
        }
    }

    printf("1\n");
    return 0;
}
